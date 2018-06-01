#pragma once
#include "Texture.h"

class RenderTarget : Uncopyable
{
public:
	RenderTarget();

	~RenderTarget();

	void Create(ID3D11Texture2D* m_pRenderTarget, ID3D11Texture2D* m_pDepthStencil, int width, int height, bool isBackBuffer);

	ID3D11RenderTargetView* GetRenderTarget()
	{
		return m_pRenderTarget;
	}

	ID3D11DepthStencilView* GetDepthStencil()
	{
		return m_pDepthStencil;
	}

private:
	ID3D11DepthStencilView*					m_pDepthStencil;
	ID3D11RenderTargetView*					m_pRenderTarget;
	ID3D11Texture2D*						m_pRenderTargetTexture;
	ID3D11Texture2D*						m_pDepthStencilTexture;
	int										m_width;
	int										m_height;
};
