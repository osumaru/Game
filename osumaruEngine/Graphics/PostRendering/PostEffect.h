#pragma once

class CPostEffect
{
public:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	~CPostEffect();

	/*
	初期化関数
	swapChain		バックバッファ取得用のスワップチェインインスタンス
	*/
	void Init(IDXGISwapChain* swapChain);

	//描画関数
	void Draw();

	ID3D11DepthStencilView* GetDepthStencil()
	{
		return m_pBackDepthStencilView;
	}

private:
	CPrimitive								m_primitive;			//プリミティブ
	CShader									m_vertexShader;			//頂点シェーダー
	CShader									m_pixelShader;			//ピクセルシェーダー
	CRenderTarget							m_backBuffer;			//バックバッファ
	ID3D11RenderTargetView*					m_pBackRenderTargetView = nullptr;//バックバッファのRTV
	ID3D11DepthStencilView*					m_pBackDepthStencilView = nullptr;//バックバッファのDSV
};