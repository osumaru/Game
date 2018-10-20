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
	width			レンダリングターゲットの幅
	height			レンダリングターゲットの高さ
	format			テクスチャのフォーマット
	pRenderTarget	レンダリングターゲットに使うテクスチャ
	*/
	void CreateRenderTarget(int width, int height, DXGI_FORMAT format, ID3D11Texture2D* pRenderTarget = nullptr);


	/*
	デプスステンシルバッファの作成
	width			レンダリングターゲットの幅
	height			レンダリングターゲットの高さ
	format			テクスチャのフォーマット
	pRenderTarget	レンダリングターゲットに使うテクスチャ
	*/
	void CreateDepthStencilBuffer(int width, int height);

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

	//レンダリングターゲット用のテクスチャの取得
	ID3D11Texture2D* GetRenderTargetTexture() const
	{
		return m_pD3DRenderTargetTexture;
	}


	//デプスステンシルテクスチャ
	ID3D11Texture2D* GetDepthStencilTexture() const
	{
		return m_pD3DDepthStencilTexture;
	}

	//レンダリングターゲットのテクスチャを取得
	CTexture& GetRenderTargetTexture()
	{
		return *m_pRenderTargetTexture;
	}

	//デプスステンシルバッファのテクスチャを取得
	CTexture& GetDepthStencilTexture()
	{
		return *m_pDepthStencilTexture;
	}
private:
	ID3D11DepthStencilView*					m_pDepthStencil;		//デプスステンシルビュー
	ID3D11RenderTargetView*					m_pRenderTarget;		//レンダリングターゲット
	ID3D11Texture2D*						m_pD3DRenderTargetTexture;	//レンダリングターゲット用のテクスチャ
	ID3D11Texture2D*						m_pD3DDepthStencilTexture;	//デプスステンシル用のテクスチャ
	int										m_width;				//レンダリングターゲットの幅
	int										m_height;				//レンダリングターゲットの高さ
	std::unique_ptr<CTexture>				m_pRenderTargetTexture;	//レンダリングターゲット用のテクスチャ
	std::unique_ptr<CTexture>				m_pDepthStencilTexture;
};
