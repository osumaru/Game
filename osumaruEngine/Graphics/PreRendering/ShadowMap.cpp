#include "engineStdafx.h"
#include "ShadowMap.h"
#include "../../Graphics/SkinModel.h"
#include "../PostEffect/Deferred.h"
#include "../../Engine.h"

void CShadowMap::Init()
{
	m_renderTarget.Create(500, 500);

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
	for (auto& model : m_modelList)
	{
		model->Draw(Engine().GetDeferred().GetViewMatrix(), Engine().GetDeferred().GetProjMatrix(), true);
	}
	m_modelList.clear();
}