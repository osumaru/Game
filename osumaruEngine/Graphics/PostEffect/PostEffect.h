#pragma once

class PostEffect
{
public:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	void Init(IDXGISwapChain* swapChain);

	void Draw();
private:
	CPrimitive								m_primitive;
	CShader									m_vertexShader;		//頂点シェーダー
	CShader									m_pixelShader;		//ピクセルシェーダー
	CTexture								m_depthStencilTexture;
	CRenderTarget							m_backBuffer;
	ID3D11RenderTargetView*					m_pBackBuffer;
	ID3D11DepthStencilView*					m_depthStencil;
};