#pragma once
enum EnViewPortState
{
	enViewPortShadow,	//シャドウマップ用のビューポート設定
	enViewPortGame,		//ゲームシーン用のビューポート設定
	enViewPortBloom00,
	enViewPortBloom01,
	enViewPortBloom10,
	enViewPortBloom11,
	enViewPortBloom20,
	enViewPortBloom21,
	enViewPortBloom30,
	enViewPortBloom31,
	enViewPortBloom40,
	enViewPortBloom41,
	enViewPortBloomCombine,
	enViewPortNum
};

//ビューポートの設定を管理するクラス
class CViewPortState
{
public:
	//初期化
	void Init();

	/*
	ビューポート設定を変更
	deviceContext		グラフィックデバイス
	viewPortNum			ビューポート設定
	*/
	void SetViewPort(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, EnViewPortState viewPortNum)
	{
		m_currentState = viewPortNum;
		deviceContext->RSSetViewports(1, &m_viewPort[m_currentState]);
	}

	//現在の設定の番号を取得
	EnViewPortState GetCurrentState()
	{
		return m_currentState;
	}

private:
	D3D11_VIEWPORT	m_viewPort[enViewPortNum];		//ビューポート設定
	EnViewPortState	m_currentState = enViewPortGame;//現在の設定
};