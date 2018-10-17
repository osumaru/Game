#include "engineStdafx.h"
#include "ShadowMap.h"
#include "../../Graphics/SkinModel.h"
#include "../PostEffect/Deferred.h"
#include "../../Engine.h"

void CShadowMap::Init()
{
	m_renderTarget.Create(FrameBufferWidth(), FrameBufferHeight(), DXGI_FORMAT_R32G32B32A32_FLOAT);
	CMatrix mat = CMatrix::Identity;
	m_CB.Create(sizeof(CMatrix), &mat);

}

void CShadowMap::SetConstantBuffer()
{
	CMatrix lightViewProj;
	lightViewProj.Mul(m_viewMatrix, m_projectionMatrix);
	m_CB.Update(&lightViewProj);
	ID3D11Buffer* buffer = m_CB.GetBody();
	GetDeviceContext()->PSSetConstantBuffers(2, 1, &buffer);
	GetDeviceContext()->VSSetConstantBuffers(2, 1, &buffer);
}

void CShadowMap::Draw()
{

	ID3D11RenderTargetView* rtv[] = { m_renderTarget.GetRenderTarget() };
	Engine().GetDeviceContext()->OMSetRenderTargets(1, rtv, m_renderTarget.GetDepthStencil());
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Engine().GetDeviceContext()->ClearRenderTargetView(m_renderTarget.GetRenderTarget(), color);
	Engine().GetDeviceContext()->ClearDepthStencilView(m_renderTarget.GetDepthStencil(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	Engine().SetAlphaBlendState(enAlphaBlendState3D);
	Engine().SetDepthStencilState(enDepthStencilState3D);
	CMatrix viewMat = m_viewMatrix;
	CMatrix projMat = m_projectionMatrix;
	for (auto& model : m_modelList)
	{
		model->Draw(viewMat, projMat, true);
	}
	m_modelList.clear();
}

