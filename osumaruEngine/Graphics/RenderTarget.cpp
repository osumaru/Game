#include "engineStdafx.h"
#include "RenderTarget.h"

CRenderTarget::CRenderTarget()
{
	m_pRenderTarget = nullptr;
	m_pDepthStencil = nullptr;
	m_pD3DRenderTargetTexture = nullptr;
	m_pD3DDepthStencilTexture = nullptr;
}

CRenderTarget::~CRenderTarget()
{
}

void CRenderTarget::CreateRenderTarget(int width, int height, DXGI_FORMAT format, ID3D11Texture2D* pRenderTarget)
{
	m_pD3DRenderTargetTexture = pRenderTarget;
	HRESULT hr;
	//バックバッファである場合それを元にしてレンダリングターゲットを作る
	if (m_pD3DRenderTargetTexture != nullptr)
	{
		GetDevice()->CreateRenderTargetView(m_pD3DRenderTargetTexture.Get(), NULL, m_pRenderTarget.GetAddressOf());
	}
	else
	{
		m_pRenderTargetTexture = std::make_unique<CTexture>();
		m_pRenderTargetTexture->Create(width, height, CTexture::enRendertarget, format);
		m_pD3DRenderTargetTexture = m_pRenderTargetTexture->GetTexture2D();
		D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
		m_pD3DRenderTargetTexture->GetDesc(&renderTargetTextureDesc);
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = renderTargetTextureDesc.Format;
		renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		hr = GetDevice()->CreateRenderTargetView(m_pD3DRenderTargetTexture.Get(), &renderTargetDesc, m_pRenderTarget.GetAddressOf());
	}
}

void CRenderTarget::CreateDepthStencilBuffer(int width, int height)
{
	m_pDepthStencilTexture = std::make_unique<CTexture>();
	m_pDepthStencilTexture->Create(width, height, CTexture::enDepthStencil, DXGI_FORMAT_D32_FLOAT);
	m_pD3DDepthStencilTexture = m_pDepthStencilTexture->GetTexture2D();
	//デプスステンシルバッファを作る
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc;
	m_pD3DDepthStencilTexture->GetDesc(&depthStencilTextureDesc);
	D3D11_DEPTH_STENCIL_VIEW_DESC descDepthStencilView;
	ZeroMemory(&descDepthStencilView, sizeof(descDepthStencilView));
	descDepthStencilView.Format = depthStencilTextureDesc.Format;
	descDepthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepthStencilView.Texture2D.MipSlice = 0;

	HRESULT hr = GetDevice()->CreateDepthStencilView(m_pD3DDepthStencilTexture.Get(), &descDepthStencilView, m_pDepthStencil.GetAddressOf());
}