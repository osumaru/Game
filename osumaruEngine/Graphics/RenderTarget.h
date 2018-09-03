#pragma once
#include "Texture.h"
//レンダリングターゲットクラス

class CRenderTarget : Uncopyable
{
public:
	//コンストラクタ
	CRenderTarget();

	//デストラクタ
	~CRenderTarget();

	/*
	レンダリングターゲットの作成
	pRenderTarget	レンダリングターゲットに使うテクスチャ
	pDepthStencil	デプスステンシルバッファに使うテクスチャ
	width			レンダリングターゲットの幅
	height			レンダリングターゲットの高さ
	isBackBuffer	バックバッファかどうか
	*/
	void Create(ID3D11Texture2D* pRenderTarget, ID3D11Texture2D* pDepthStencil, int width, int height, bool isBackBuffer);

	//レンダリングターゲットの取得
	ID3D11RenderTargetView* GetRenderTarget() const
	{
		return m_pRenderTarget;
	}

	//デプスステンシルバッファの取得
	ID3D11DepthStencilView* GetDepthStencil() const
	{
		return m_pDepthStencil;
	}

private:
	ID3D11DepthStencilView*					m_pDepthStencil;		//デプスステンシルビュー
	ID3D11RenderTargetView*					m_pRenderTarget;		//レンダリングターゲット
	ID3D11Texture2D*						m_pRenderTargetTexture;	//レンダリングターゲット用のテクスチャ	
	ID3D11Texture2D*						m_pDepthStencilTexture;	//デプスステンシル用のテクスチャ
	int										m_width;				//レンダリングターゲットの幅
	int										m_height;				//レンダリングターゲットの高さ
};
