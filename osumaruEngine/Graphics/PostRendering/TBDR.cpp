#include "TBDR.h"
#include "../../Camera/Camera.h"

void CTBDR::Init()
{
	m_cs.Load("Assets/shader/TBDR.fx", "CSMain", CShader::enCS);
	m_pointLightCB.Create(sizeof(SPointLightCB), nullptr);
}

void CTBDR::Draw()
{
	if (!m_isActive)
	{
		return;
	}
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
	GetDeviceContext()->CSSetShader((ID3D11ComputeShader*)m_cs.GetBody().Get(), nullptr, 0);
	ID3D11Buffer* cb[] = { m_pointLightCB.GetBody().Get() };
	ID3D11ShaderResourceView* mainSrv = { MainRenderTarget().GetRenderTargetTexture().GetShaderResource().Get() };
	Engine().SwitchingRenderTarget();
	ID3D11RenderTargetView* backBuffer[] = { MainRenderTarget().GetRenderTarget().Get() };
	GetDeviceContext()->OMSetRenderTargets(1, backBuffer, MainRenderTarget().GetDepthStencil().Get());
	float color[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	GetDeviceContext()->ClearRenderTargetView(MainRenderTarget().GetRenderTarget().Get(), color);
	GetDeviceContext()->ClearDepthStencilView(MainRenderTarget().GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	ID3D11ShaderResourceView* srviews[3] = {
			mainSrv,
			Engine().GetDeferred().GetShaderResource(enRenderTargetDepth).Get(),
			Engine().GetDeferred().GetShaderResource(enRenderTargetNormal).Get()
	};
	GetDeviceContext()->CSSetConstantBuffers(0, 1, cb);
	GetDeviceContext()->CSSetShaderResources(0, 3, srviews);
	ID3D11UnorderedAccessView* uaviews[] = { MainRenderTarget().GetRenderTargetTexture().GetUnorderedAccessView().Get() };
	UINT initialCount = 0;
	GetDeviceContext()->CSSetUnorderedAccessViews(3, 1, uaviews, &initialCount);
	GetDeviceContext()->Dispatch(FrameBufferWidth() / 16, FrameBufferHeight() / 16, 1);
	uaviews[0] = nullptr;
	GetDeviceContext()->CSSetUnorderedAccessViews(3, 1, uaviews, &initialCount);
}