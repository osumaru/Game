#include "Bloom.h"


void CBloom::Init()
{
	m_luminanceTarget.CreateRenderTarget(FrameBufferWidth(), FrameBufferHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_luminanceTarget.CreateDepthStencilBuffer(FrameBufferWidth(), FrameBufferHeight());
	m_combineTarget.CreateRenderTarget(FrameBufferWidth() / 2, FrameBufferHeight() / 2, DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_combineTarget.CreateDepthStencilBuffer(FrameBufferWidth() / 2, FrameBufferHeight() / 2);

	for (int i = 0; i < DOWN_SAMPLING_NUM; i++)
	{
		m_downSamplingTarget[i][0].CreateRenderTarget(FrameBufferWidth() >> i + 1, FrameBufferHeight() >> i, DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_downSamplingTarget[i][0].CreateDepthStencilBuffer(FrameBufferWidth() >> i + 1, FrameBufferHeight() >> i);
		m_downSamplingTarget[i][1].CreateRenderTarget(FrameBufferWidth() >> i + 1, FrameBufferHeight() >> i + 1, DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_downSamplingTarget[i][1].CreateDepthStencilBuffer(FrameBufferWidth() >> i + 1, FrameBufferHeight() >> i + 1);
	}
	VSLayout vertexBuffer[4] =
	{
		{ {-1.0f,  1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
		{ { 1.0f,  1.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
		{ { 1.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
		{ {-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} }
	};
	WORD indexbuffer[6] = { 0, 2, 1, 0, 3, 2 };
	m_primitive.Create(vertexBuffer, sizeof(VSLayout), 4, indexbuffer, 6, CPrimitive::enIndex16, CPrimitive::enTypeTriangleList);

	m_mainVS.Load("Assets/shader/bloom.fx", "VSMain", CShader::enVS);
	m_mainPS.Load("Assets/shader/bloom.fx", "PSMain", CShader::enPS);
	m_finalPS.Load("Assets/shader/bloom.fx", "FinalPS", CShader::enPS);
	m_BlurPS.Load("Assets/shader/bloom.fx", "BlurPS", CShader::enPS);
	m_combinePS.Load("Assets/shader/bloom.fx", "CombinePS", CShader::enPS);
	m_XBlurVS.Load("Assets/shader/bloom.fx", "XBlurVS", CShader::enVS);
	m_YBlurVS.Load("Assets/shader/bloom.fx", "YBlurVS", CShader::enVS);
	m_cb.Create(sizeof(SBloomCB), nullptr);
	SetWeight(3.0f);
	m_sampler.Init(enAddressingModeClamp, enFilterLinear);
	m_isActive = true;
}

void CBloom::SetWeight(float rate)
{
	float total = 0.0f;
	for (int i = 0; i < BLUR_RANGE; i++)
	{
		m_weight[i] = expf(-0.5f * float(i * i) / rate);
		total += 2.0f * m_weight[i];
	}
	for (int i = 0; i < BLUR_RANGE; i++)
	{
		m_weight[i] /= total;
	}
}

void CBloom::Draw()
{
	if (!m_isActive)
	{
		return;
	}

	EnViewPortState backupViewPortState = Engine().GetCurrentViewPortState();
	EnDepthStencilState zenableBackup = Engine().GetCurrentDepthStencilState();
	Engine().SetDepthStencilState(enDepthStencilState2D);
	ID3D11DeviceContext* deviceContext = GetDeviceContext();
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//輝度抽出
	{
		Engine().SetViewPortState(enViewPortGame);
		deviceContext->OMSetRenderTargets(1, m_luminanceTarget.GetRenderTarget().GetAddressOf(), m_luminanceTarget.GetDepthStencil().Get());
		
		deviceContext->ClearRenderTargetView(m_luminanceTarget.GetRenderTarget().Get(), clearColor);
		deviceContext->ClearDepthStencilView(m_luminanceTarget.GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		deviceContext->VSSetShader((ID3D11VertexShader*)m_mainVS.GetBody().Get(), nullptr, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_mainPS.GetBody().Get(), nullptr, 0);
		deviceContext->IASetInputLayout(m_mainVS.GetInputlayOut().Get());
		ID3D11ShaderResourceView* srv = MainRenderTarget().GetRenderTargetTexture().GetShaderResource().Get();
		deviceContext->PSSetShaderResources(5, 1, &srv);

		m_primitive.Draw(deviceContext);
	}
	int count = 0;
	EnViewPortState viewPortState[] = 
	{
		enViewPortBloom00,
		enViewPortBloom01,
		enViewPortBloom10,
		enViewPortBloom11,
		enViewPortBloom20,
		enViewPortBloom21,
		enViewPortBloom30,
		enViewPortBloom31,
		enViewPortBloom40,
		enViewPortBloom41,
	};

	for (int i = 0; i < DOWN_SAMPLING_NUM; i++)
	{
		SBloomCB cb;
		//X方向へのブラー
		{
			Engine().SetViewPortState(viewPortState[count]);
			ID3D11RenderTargetView* rtv = m_downSamplingTarget[i][0].GetRenderTarget().Get();
			deviceContext->OMSetRenderTargets(1, &rtv, m_downSamplingTarget[i][0].GetDepthStencil().Get());
			deviceContext->VSSetShader((ID3D11VertexShader*)m_XBlurVS.GetBody().Get(), nullptr, 0);
			deviceContext->PSSetShader((ID3D11PixelShader*)m_BlurPS.GetBody().Get(), nullptr, 0);
			deviceContext->IASetInputLayout(m_XBlurVS.GetInputlayOut().Get());
			
			ID3D11ShaderResourceView* srv;
			if (i == 0)
			{
				srv = m_luminanceTarget.GetRenderTargetTexture().GetShaderResource().Get();

				cb.offset.x = 16.0f / m_luminanceTarget.GetRenderTargetTexture().GetWidth();
				cb.offset.y = 0.0f;

				cb.textureSize.x = m_luminanceTarget.GetRenderTargetTexture().GetWidth();
				cb.textureSize.y = m_luminanceTarget.GetRenderTargetTexture().GetHeight();
			}
			else
			{
				srv = m_downSamplingTarget[i - 1][1].GetRenderTargetTexture().GetShaderResource().Get();

				cb.offset.x = 16.0f / m_downSamplingTarget[i - 1][1].GetRenderTargetTexture().GetWidth();
				cb.offset.y = 0.0f;
				cb.textureSize.x = m_downSamplingTarget[i - 1][1].GetRenderTargetTexture().GetWidth();
				cb.textureSize.y = m_downSamplingTarget[i - 1][1].GetRenderTargetTexture().GetHeight();
			}
			deviceContext->PSSetShaderResources(5, 1, &srv);
			memcpy(&cb.weight1, m_weight, sizeof(CVector4));
			memcpy(&cb.weight2, m_weight + 4, sizeof(CVector4));
			m_cb.Update(&cb);
			ID3D11Buffer* buffer = m_cb.GetBody().Get();
			
			ID3D11SamplerState* sampler = m_sampler.GetBody();
			deviceContext->VSSetSamplers(1, 1, &sampler);
			deviceContext->PSSetSamplers(1, 1, &sampler);
			deviceContext->PSSetConstantBuffers(0, 1, &buffer);
			deviceContext->VSSetConstantBuffers(0, 1, &buffer);
			m_primitive.Draw(deviceContext);
			count++;
		}
		//Y方向へのブラー
		{
			Engine().SetViewPortState(viewPortState[count]);
			ID3D11RenderTargetView* rtv = m_downSamplingTarget[i][1].GetRenderTarget().Get();
			ID3D11DepthStencilView* dsv = m_downSamplingTarget[i][1].GetDepthStencil().Get();
			deviceContext->OMSetRenderTargets(1, &rtv, dsv);
			deviceContext->VSSetShader((ID3D11VertexShader*)m_YBlurVS.GetBody().Get(), nullptr, 0);
			deviceContext->PSSetShader((ID3D11PixelShader*)m_BlurPS.GetBody().Get(), nullptr, 0);
			deviceContext->IASetInputLayout(m_YBlurVS.GetInputlayOut().Get());
			ID3D11ShaderResourceView* srv = m_downSamplingTarget[i][0].GetRenderTargetTexture().GetShaderResource().Get();
			deviceContext->PSSetShaderResources(5, 1, &srv);
			cb.offset = { 0.0f, 16.0f / m_downSamplingTarget[i][0].GetRenderTargetTexture().GetWidth(), 0.0f, 0.0f };
			cb.textureSize = { (float)m_downSamplingTarget[i][0].GetRenderTargetTexture().GetWidth(), (float)m_downSamplingTarget[i][0].GetRenderTargetTexture().GetHeight(), 0.0f, 0.0f };
			m_cb.Update(&cb);
			ID3D11Buffer* buffer = m_cb.GetBody().Get();
			deviceContext->PSSetConstantBuffers(0, 1, &buffer);
			deviceContext->VSSetConstantBuffers(0, 1, &buffer);
			ID3D11SamplerState* sampler = m_sampler.GetBody();
			deviceContext->VSSetSamplers(1, 1, &sampler);
			deviceContext->PSSetSamplers(1, 1, &sampler);
			m_primitive.Draw(deviceContext);
			count++;
		}
	}
	//ぼかし合成
	{
		Engine().SetViewPortState(enViewPortBloomCombine);
		ID3D11RenderTargetView* rtv = m_combineTarget.GetRenderTarget().Get();
		ID3D11DepthStencilView* dsv = m_combineTarget.GetDepthStencil().Get();

		deviceContext->OMSetRenderTargets(1, &rtv, dsv);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_combinePS.GetBody().Get(), 0, 0);
		deviceContext->VSSetShader((ID3D11VertexShader*)m_mainVS.GetBody().Get(), 0, 0);
		deviceContext->IASetInputLayout(m_mainVS.GetInputlayOut().Get());
		ID3D11ShaderResourceView* srv[] = {
			m_downSamplingTarget[0][1].GetRenderTargetTexture().GetShaderResource().Get(),
			m_downSamplingTarget[1][1].GetRenderTargetTexture().GetShaderResource().Get(),
			m_downSamplingTarget[2][1].GetRenderTargetTexture().GetShaderResource().Get(),
			m_downSamplingTarget[3][1].GetRenderTargetTexture().GetShaderResource().Get(),
			m_downSamplingTarget[4][1].GetRenderTargetTexture().GetShaderResource().Get(),
		};
		deviceContext->PSSetShaderResources(0, 5, srv);
		ID3D11SamplerState* sampler = m_sampler.GetBody();
		deviceContext->VSSetSamplers(1, 1, &sampler);
		deviceContext->PSSetSamplers(1, 1, &sampler);
		m_primitive.Draw(deviceContext);
	}
	//最終合成
	{
		
		Engine().SetViewPortState(enViewPortGame);
		ID3D11RenderTargetView* rtv = MainRenderTarget().GetRenderTarget().Get();
		ID3D11DepthStencilView* dsv = MainRenderTarget().GetDepthStencil().Get();
		deviceContext->OMSetRenderTargets(1, &rtv, dsv);
		EnAlphaBlendState currentBlendState = Engine().GetCurrentAlphaBlendState();
		Engine().SetAlphaBlendState(enAlphaBlendStateAdd);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_finalPS.GetBody().Get(), 0, 0);
		deviceContext->VSSetShader((ID3D11VertexShader*)m_mainVS.GetBody().Get(), 0, 0);
		deviceContext->IASetInputLayout(m_mainVS.GetInputlayOut().Get());
		ID3D11ShaderResourceView* srv = m_combineTarget.GetRenderTargetTexture().GetShaderResource().Get();
		deviceContext->PSSetShaderResources(5, 1, &srv);
		ID3D11SamplerState* sampler = m_sampler.GetBody();
		deviceContext->VSSetSamplers(1, 1, &sampler);
		deviceContext->PSSetSamplers(1, 1, &sampler);
		m_primitive.Draw(deviceContext);
		Engine().SetAlphaBlendState(currentBlendState);

	}
	Engine().SetViewPortState(backupViewPortState);
	Engine().SetDepthStencilState(zenableBackup);

}