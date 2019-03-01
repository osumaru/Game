#pragma once
#include "Bloom.h"
#include "MotionBlur.h"

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
	void Init(Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain);

	//描画関数
	void Draw();

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencil()
	{
		return m_pBackDepthStencilView;
	}

	CBloom& GetBloom()
	{
		return m_bloom;
	}

private:
	CBloom											m_bloom;
	CMotionBlur										m_motionBlur;
	CPrimitive										m_primitive;			//プリミティブ
	CShader											m_vertexShader;			//頂点シェーダー
	CShader											m_pixelShader;			//ピクセルシェーダー
	CRenderTarget									m_backBuffer;			//バックバッファ
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pBackRenderTargetView = nullptr;//バックバッファのRTV
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pBackDepthStencilView = nullptr;//バックバッファのDSV
};