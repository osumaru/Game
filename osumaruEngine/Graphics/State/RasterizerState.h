#pragma once

enum EnRasterizerState
{
	enRasterizerState3D,
	enRasterizerState2D,
	enRasterizerStateNum,

};
//ラスタライザの設定を管理するクラス
class CRasterizerState : Uncopyable
{
public:

	//初期化
	void Init(ID3D11Device* device);

	/*
	ラスタライザの設定を変更
	deviceContext		グラフィックデバイス
	rasterizerState		ラスタライザの設定
	*/
	void SetRasterizerState(ID3D11DeviceContext* deviceContext, EnRasterizerState rasterizerState)
	{
		m_currentState = rasterizerState;
		deviceContext->RSSetState(m_rasterizerState[m_currentState]);
	}

	//ラスタライザの現在の設定を取得
	EnRasterizerState GetCurrentState() const
	{
		return m_currentState;
	}

private:
	ID3D11RasterizerState*	m_rasterizerState[enRasterizerStateNum];	//ラスタライザ
	EnRasterizerState		m_currentState = enRasterizerState2D;		//現在の設定
};