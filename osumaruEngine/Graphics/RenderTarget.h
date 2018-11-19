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
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTarget()
	{
		return m_pRenderTarget;
	}

	//デプスステンシルバッファの取得
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencil()
	{
		return m_pDepthStencil;
	}

	//レンダリングターゲット用のテクスチャの取得
	Microsoft::WRL::ComPtr<ID3D11Texture2D> GetRenderTargetTexture2D()
	{
		return m_pD3DRenderTargetTexture;
	}


	//デプスステンシルテクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D>& GetDepthStencilTexture2D()
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
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>			m_pDepthStencil;			//デプスステンシルビュー
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			m_pRenderTarget;			//レンダリングターゲット
	Microsoft::WRL::ComPtr<ID3D11Texture2D>					m_pD3DRenderTargetTexture;	//レンダリングターゲット用のテクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D>					m_pD3DDepthStencilTexture;	//デプスステンシル用のテクスチャ
	int														m_width;					//レンダリングターゲットの幅
	int														m_height;					//レンダリングターゲットの高さ
	std::unique_ptr<CTexture>								m_pRenderTargetTexture;		//レンダリングターゲット用のテクスチャ
	std::unique_ptr<CTexture>								m_pDepthStencilTexture;
};
