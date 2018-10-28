#include "engineStdafx.h"
#include "Deferred.h"
#include "../../Camera/Camera.h"
#include "../SkinModelShaderFlgCommon.h"
#include "../../Engine.h"

CDeferred::CDeferred()
{

}

void CDeferred::SetCamera(const CCamera* camera)
{
	m_camera = camera;
	CMatrix mat;
	mat.Mul(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
	mat.Inverse();
	m_gameCameraCB.Create(sizeof(CMatrix), &mat);
}

void CDeferred::Init()
{
	for (int i = 0; i < enRenderTargetNum; i++)
	{
		DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		switch (i)
		{
		case enRenderTargetMaterial:
			format = DXGI_FORMAT_R32G32B32A32_SINT;
			break;
		default:
			break;
		}
		m_renderTarget[i].CreateRenderTarget(FrameBufferWidth(), FrameBufferHeight(), format);
	}
	m_renderTarget[0].CreateDepthStencilBuffer(FrameBufferWidth(), FrameBufferHeight());

	SFrameSizeCB frameSizeCB;
	frameSizeCB.frameBufferWidth = FrameBufferWidth();
	frameSizeCB.frameBufferHeight = FrameBufferHeight();
	m_frameSizeCB.Create(sizeof(SFrameSizeCB), &frameSizeCB);
	m_materialCB.Create(sizeof(SMaterialFlg), &g_materialFlg);
	m_lightCB.Create(sizeof(CLight), &Light());
	m_vertexShader.Load("Assets/shader/deferred.fx", "VSMain", CShader::enVS);
	m_pixelShader.Load("Assets/shader/deferred.fx", "PSMain", CShader::enPS);
	SVSLayout vertexBufferLayout[4] =
	{
		{ { -1.0f,  1.0f, 0.0f, 1.0f } , { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f, 1.0f } , { 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, 0.0f, 1.0f } , { 0.0f, 1.0f } },
		{ {  1.0f, -1.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },
	};
	m_cs.Load("Assets/shader/TBDR.fx", "CSMain", CShader::enCS);
	m_pointLightCB.Create(sizeof(SPointLightCB), nullptr);
	DWORD indexBufferLayout[4] = { 0, 2, 1, 3 };
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);
	m_lightCB.Create(sizeof(CLight), &Light());
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MaxAnisotropy = 1;
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	GetDevice()->CreateSamplerState(&desc, &m_pAnisotropicSampler);
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	GetDevice()->CreateSamplerState(&desc, &m_pLinearSampler);
}

void CDeferred::Start()
{
	float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	float materialColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float depthColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	ID3D11RenderTargetView* mainViews[enRenderTargetNum];
	for (int i = 0; i < enRenderTargetNum;i++)
	{
		mainViews[i] = m_renderTarget[i].GetRenderTarget();
	};
	GetDeviceContext()->ClearDepthStencilView(Engine().GetPostEffect().GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	GetDeviceContext()->OMSetRenderTargets(enRenderTargetNum, mainViews, Engine().GetPostEffect().GetDepthStencil());
	Engine().SetAlphaBlendState(enAlphaBlendStateNone);
	Engine().SetDepthStencilState(enDepthStencilState3D);
	Engine().SetRasterizerState(enRasterizerState3D);
	float *pColor = color;
	for (int i = 0; i < enRenderTargetNum; i++)
	{
		switch (i)
		{
		case enRenderTargetDepth:
			pColor = depthColor;
			break;
		case enRenderTargetMaterial:
			pColor = materialColor;
			break;
		default:
			pColor = color;
			break;
		}
		GetDeviceContext()->ClearRenderTargetView(m_renderTarget[i].GetRenderTarget(), pColor);
	}
	GetDeviceContext()->ClearDepthStencilView(m_renderTarget[0].GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}


void CDeferred::Draw()
{
	{
		float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
		ID3D11RenderTargetView* backBuffer[] = { MainRenderTarget().GetRenderTarget() };
		GetDeviceContext()->OMSetRenderTargets(1, backBuffer, MainRenderTarget().GetDepthStencil());

		GetDeviceContext()->ClearRenderTargetView(backBuffer[0], color);
		GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		ID3D11ShaderResourceView* srviews[enRenderTargetNum + 1];
		for (int i = 0; i < enRenderTargetNum; i++)
		{
			srviews[i] = m_renderTarget[i].GetRenderTargetTexture().GetShaderResource();
		};
		srviews[enRenderTargetNum] = Engine().GetShadowMap().GetRenderTarget().GetRenderTargetTexture().GetShaderResource();
		CLight light = Light();
		m_lightCB.Update(&Light());
		Engine().GetShadowMap().SetConstantBuffer();
		ID3D11Buffer* buffer;
		if (m_camera != nullptr)
		{
			CMatrix gameCameraMat;
			gameCameraMat.Mul(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
			//gameCameraMat.Inverse();
			m_gameCameraCB.Update(&gameCameraMat);
			buffer = m_gameCameraCB.GetBody();
			GetDeviceContext()->PSSetConstantBuffers(1, 1, &buffer);
		}
		buffer = m_lightCB.GetBody();
		GetDeviceContext()->PSSetConstantBuffers(0, 1, &buffer);
		buffer = m_materialCB.GetBody();
		GetDeviceContext()->PSSetConstantBuffers(3, 1, &buffer);
		buffer = m_frameSizeCB.GetBody();
		GetDeviceContext()->PSSetConstantBuffers(4, 1, &buffer);
		GetDeviceContext()->PSSetShaderResources(0, enRenderTargetNum + 1, srviews);
		GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody(), nullptr, 0);
		GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody(), nullptr, 0);
		ID3D11SamplerState* samplers[] = { m_pAnisotropicSampler };
		GetDeviceContext()->PSSetSamplers(1, 1, samplers);
		ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer() };
		UINT strides[] = { m_primitive.GetVertexStride() };
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
		GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
		GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer(), m_primitive.GetIndexFormat(), 0);
		GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut());
		GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
	}
	{
		SPointLightCB plcb;
		plcb.screenParam = { (float)FrameBufferWidth(), (float)FrameBufferHeight() };
		plcb.projectionMat = CMatrix::Identity;
		plcb.viewMat = CMatrix::Identity;
		plcb.viewMatRotOnry = CMatrix::Identity;
		if (m_camera != nullptr)
		{
			CMatrix viewMat = m_camera->GetViewMatrix();
			plcb.viewMat = viewMat;
			plcb.viewMatRotOnry = viewMat;
			plcb.viewMatRotOnry.m[3][0] = 0.0f;
			plcb.viewMatRotOnry.m[3][1] = 0.0f;
			plcb.viewMatRotOnry.m[3][2] = 0.0f;
			plcb.projectionMat = m_camera->GetProjectionMatrix();
			Engine().GetPointLightManager().Draw(viewMat);
		}
		m_pointLightCB.Update(&plcb);
		GetDeviceContext()->CSSetShader((ID3D11ComputeShader*)m_cs.GetBody(), nullptr, 0);
		ID3D11Buffer* cb[] = { m_pointLightCB.GetBody() };
		ID3D11ShaderResourceView* mainSrv = { MainRenderTarget().GetRenderTargetTexture().GetShaderResource()};
		Engine().SwitchingRenderTarget(); 
		ID3D11RenderTargetView* backBuffer[] = { MainRenderTarget().GetRenderTarget() };
		GetDeviceContext()->OMSetRenderTargets(1, backBuffer, MainRenderTarget().GetDepthStencil());
		float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
		GetDeviceContext()->ClearRenderTargetView(MainRenderTarget().GetRenderTarget(), color);
		GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		ID3D11ShaderResourceView* srviews[3] = {
				mainSrv,
				m_renderTarget[enRenderTargetDepth].GetRenderTargetTexture().GetShaderResource(),
				m_renderTarget[enRenderTargetNormal].GetRenderTargetTexture().GetShaderResource()
		};
		GetDeviceContext()->CSSetConstantBuffers(0, 1, cb);
		GetDeviceContext()->CSSetShaderResources(0, 3, srviews);
		ID3D11UnorderedAccessView* uaviews[] = { MainRenderTarget().GetRenderTargetTexture().GetUnorderedAccessView() };
		UINT initialCount = 0;
		GetDeviceContext()->CSSetUnorderedAccessViews(3, 1, uaviews, &initialCount);
		GetDeviceContext()->Dispatch(FrameBufferWidth() / 16, FrameBufferHeight() / 16, 1);
		uaviews[0] = nullptr;
		GetDeviceContext()->CSSetUnorderedAccessViews(3, 1, uaviews, &initialCount);


	}
}
