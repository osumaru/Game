#include "engineStdafx.h"
#include "RenderTarget.h"

CRenderTarget::CRenderTarget()
{
	m_pRenderTarget = nullptr;
	m_pDepthStencil = nullptr;
}

CRenderTarget::~CRenderTarget()
{
	if (m_pRenderTarget != nullptr)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}
	if (m_pDepthStencil != nullptr)
	{
		m_pDepthStencil->Release();
		m_pDepthStencil = nullptr;
	}
	m_pRenderTargetTexture->Release();
	m_pDepthStencilTexture->Release();

}

void CRenderTarget::Create(ID3D11Texture2D* pRenderTarget, ID3D11Texture2D* pDepthStencil, int width, int height, bool isBackBuffer)
{
	m_pRenderTargetTexture = pRenderTarget;
	m_pDepthStencilTexture = pDepthStencil;
	m_pRenderTargetTexture->AddRef();
	m_pDepthStencilTexture->AddRef();
	HRESULT hr;
	//バックバッファである場合それを元にしてレンダリングターゲットを作る
	if (isBackBuffer)
	{
		GetDevice()->CreateRenderTargetView(m_pRenderTargetTexture, NULL, &m_pRenderTarget);
	}
	else
	{
		D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
		m_pRenderTargetTexture->GetDesc(&renderTargetTextureDesc);
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = renderTargetTextureDesc.Format;
		renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		hr = GetDevice()->CreateRenderTargetView(m_pRenderTargetTexture, &renderTargetDesc, &m_pRenderTarget);
	}
	//デプスステンシルバッファを作る
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc;
	m_pDepthStencilTexture->GetDesc(&depthStencilTextureDesc);
	D3D11_DEPTH_STENCIL_VIEW_DESC descDepthStencilView;
	ZeroMemory(&descDepthStencilView, sizeof(descDepthStencilView));
	descDepthStencilView.Format = depthStencilTextureDesc.Format;
	descDepthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepthStencilView.Texture2D.MipSlice = 0;

	hr = GetDevice()->CreateDepthStencilView(pDepthStencil, &descDepthStencilView, &m_pDepthStencil);
}