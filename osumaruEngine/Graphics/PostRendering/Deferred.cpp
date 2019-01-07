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

	SDefferedCB defferedCB;
	defferedCB.frameBufferWidth = FrameBufferWidth();
	defferedCB.frameBufferHeight = FrameBufferHeight();
	m_defferedCB.Create(sizeof(SDefferedCB), &defferedCB);
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
	DWORD indexBufferLayout[4] = { 0, 2, 1, 3 };
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);

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
	m_gameCameraCB.Create(sizeof(CMatrix), nullptr);
}

void CDeferred::Start()
{
	float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	float materialColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float depthColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	ID3D11RenderTargetView* mainViews[enRenderTargetNum];
	for (int i = 0; i < enRenderTargetNum;i++)
	{
		mainViews[i] = m_renderTarget[i].GetRenderTarget().Get();
	};
	GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	GetDeviceContext()->OMSetRenderTargets(enRenderTargetNum, mainViews, MainRenderTarget().GetDepthStencil().Get());
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
		GetDeviceContext()->ClearRenderTargetView(m_renderTarget[i].GetRenderTarget().Get(), pColor);
	}
	GetDeviceContext()->ClearDepthStencilView(m_renderTarget[0].GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}


void CDeferred::Draw()
{
	{
		float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
		ID3D11RenderTargetView* backBuffer[] = { MainRenderTarget().GetRenderTarget().Get() };
		GetDeviceContext()->OMSetRenderTargets(1, backBuffer, m_renderTarget[0].GetDepthStencil().Get());

		GetDeviceContext()->ClearRenderTargetView(backBuffer[0], color);
		GetDeviceContext()->ClearDepthStencilView(m_renderTarget[0].GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		ID3D11ShaderResourceView* srviews[enRenderTargetNum + 1];
		for (int i = 0; i < enRenderTargetNum; i++)
		{
			srviews[i] = m_renderTarget[i].GetRenderTargetTexture().GetShaderResource().Get();
		};
		srviews[enRenderTargetNum] = Engine().GetShadowMap().GetRenderTarget().GetRenderTargetTexture().GetShaderResource().Get();
		CLight light = Light();
		m_lightCB.Update(&Light());
		Engine().GetShadowMap().SetConstantBuffer();
		if (m_camera != nullptr)
		{
			CMatrix gameCameraMat;
			gameCameraMat.Mul(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
			//gameCameraMat.Inverse();
			m_gameCameraCB.Update(&gameCameraMat);
			GetDeviceContext()->PSSetConstantBuffers(1, 1, m_gameCameraCB.GetBody().GetAddressOf());
		}

		SDefferedCB defferedCB;
		defferedCB.frameBufferWidth = FrameBufferWidth();
		defferedCB.frameBufferHeight = FrameBufferHeight();
		if (m_camera != nullptr)
		{
			CVector3 cameraPosition = m_camera->GetPosition();
			defferedCB.gameCameraPos.x = cameraPosition.x;
			defferedCB.gameCameraPos.y = cameraPosition.y;
			defferedCB.gameCameraPos.z = cameraPosition.z;
			defferedCB.gameCameraPos.w = 1.0f;
		}
		m_defferedCB.Update(&defferedCB);
		GetDeviceContext()->PSSetConstantBuffers(0, 1, m_lightCB.GetBody().GetAddressOf());
		GetDeviceContext()->PSSetConstantBuffers(3, 1, m_materialCB.GetBody().GetAddressOf());
		GetDeviceContext()->PSSetConstantBuffers(4, 1, m_defferedCB.GetBody().GetAddressOf());
		GetDeviceContext()->PSSetShaderResources(0, enRenderTargetNum + 1, srviews);

		ID3D11SamplerState* samplers[] = { m_pAnisotropicSampler };
		GetDeviceContext()->PSSetSamplers(1, 1, samplers);

		GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody().Get(), nullptr, 0);
		GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody().Get(), nullptr, 0);
		GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut().Get());
		m_primitive.Draw(GetDeviceContext());
	}
	{
		//SPointLightCB plcb;
		//plcb.screenParam = { (float)FrameBufferWidth(), (float)FrameBufferHeight() };
		//plcb.projectionMat = CMatrix::Identity;
		//plcb.viewMat = CMatrix::Identity;
		//plcb.viewMatRotOnry = CMatrix::Identity;
		//if (m_camera != nullptr)
		//{
		//	CMatrix viewMat = m_camera->GetViewMatrix();
		//	plcb.viewMat = viewMat;
		//	plcb.viewMatRotOnry = viewMat;
		//	plcb.viewMatRotOnry.m[3][0] = 0.0f;
		//	plcb.viewMatRotOnry.m[3][1] = 0.0f;
		//	plcb.viewMatRotOnry.m[3][2] = 0.0f;
		//	plcb.projectionMat = m_camera->GetProjectionMatrix();
		//	Engine().GetPointLightManager().Draw(viewMat);
		//}
		//m_pointLightCB.Update(&plcb);
		//GetDeviceContext()->CSSetShader((ID3D11ComputeShader*)m_cs.GetBody().Get(), nullptr, 0);
		//ID3D11Buffer* cb[] = { m_pointLightCB.GetBody().Get() };
		//ID3D11ShaderResourceView* mainSrv = { MainRenderTarget().GetRenderTargetTexture().GetShaderResource().Get()};
		//Engine().SwitchingRenderTarget(); 
		//ID3D11RenderTargetView* backBuffer[] = { MainRenderTarget().GetRenderTarget().Get() };
		//GetDeviceContext()->OMSetRenderTargets(1, backBuffer, MainRenderTarget().GetDepthStencil().Get());
		//float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
		//GetDeviceContext()->ClearRenderTargetView(MainRenderTarget().GetRenderTarget().Get(), color);
		//GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		//ID3D11ShaderResourceView* srviews[3] = {
		//		mainSrv,
		//		m_renderTarget[enRenderTargetDepth].GetRenderTargetTexture().GetShaderResource().Get(),
		//		m_renderTarget[enRenderTargetNormal].GetRenderTargetTexture().GetShaderResource().Get()
		//};
		//GetDeviceContext()->CSSetConstantBuffers(0, 1, cb);
		//GetDeviceContext()->CSSetShaderResources(0, 3, srviews);
		//ID3D11UnorderedAccessView* uaviews[] = { MainRenderTarget().GetRenderTargetTexture().GetUnorderedAccessView().Get() };
		//UINT initialCount = 0;
		//GetDeviceContext()->CSSetUnorderedAccessViews(3, 1, uaviews, &initialCount);
		//GetDeviceContext()->Dispatch(FrameBufferWidth() / 16, FrameBufferHeight() / 16, 1);
		//uaviews[0] = nullptr;
		//GetDeviceContext()->CSSetUnorderedAccessViews(3, 1, uaviews, &initialCount);


	}
}
