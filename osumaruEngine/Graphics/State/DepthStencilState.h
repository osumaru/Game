#pragma once
enum EnDepthStencilState
{
	enDepthStencilState2D,		//2D用
	enDepthStencilState3D,		//3D用
	enDepthStencilParticle,		//パーティクル用のステート(深度書き込みはしないが深度テストはする
	enDepthStencilStateNum,
};

//深度設定を管理するクラス
class CDepthStencilState : Uncopyable
{
public:

	//デストラクタ
	~CDepthStencilState();

	//初期化
	void Init(Microsoft::WRL::ComPtr<ID3D11Device> device);

	/*
	深度設定を変更
	deviceContext		グラフィックデバイス
	depthStencilState	深度設定
	*/
	void SetDepthStencilState(Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext, EnDepthStencilState depthStencilState)
	{
		m_currentState = depthStencilState;
		deviceContext->OMSetDepthStencilState(m_depthStencilState[m_currentState], 0);
	}

	//現在の設定を取得
	EnDepthStencilState GetCurrentDepthState()
	{
		return m_currentState;
	}

private:
	ID3D11DepthStencilState* m_depthStencilState[enDepthStencilStateNum] = {nullptr};	//深度ステート
	EnDepthStencilState		m_currentState = enDepthStencilState2D;						//現在の設定
};
