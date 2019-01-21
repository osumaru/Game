#pragma once

class CBloom : Uncopyable
{
public:

	//初期化
	void Init();

	//ガウスブラーのウェイトを設定
	void SetWeight(float rate);

	//描画
	void Draw();

	//アクティブフラグを設定
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	//頂点レイアウト
	struct VSLayout
	{
		CVector4 pos;
		CVector2 uv;
	};

	//定数バッファ
	struct SBloomCB
	{
		CVector4 textureSize;
		CVector4 offset;
		CVector4 weight1;
		CVector4 weight2;

	};

private:
	bool			m_isActive = false;		//アクティブかどうかのフラグ
	static const int BLUR_RANGE = 8;		//ブラーをかける範囲
	static const int DOWN_SAMPLING_NUM = 5;	//ダウンサンプリングの数
	CRenderTarget	m_downSamplingTarget[DOWN_SAMPLING_NUM][2];
	CPrimitive		m_primitive;			//プリミティブ
	CRenderTarget	m_luminanceTarget;		//輝度抽出用のレンダリングターゲット
	CRenderTarget	m_combineTarget;		//ぼかし合成用のレンダリングターゲット
	float			m_weight[BLUR_RANGE];	//ガウスブラー用のウェイト
	CShader			m_mainPS;				//メインのピクセルシェーダー
	CShader			m_mainVS;				//メインの頂点シェーダー
	CShader			m_combinePS;			//ぼかし合成用のピクセルシェーダー
	CShader			m_finalPS;				//最終合成用のピクセルシェーダー
	CShader			m_XBlurVS;				//Xブラー用の頂点シェーダー
	CShader			m_YBlurVS;				//Yブラー用の頂点シェーダー
	CShader			m_BlurPS;				//ブラー用のピクセルシェーダー
	CConstantBuffer	m_cb;					//定数バッファ
	CSamplerState	m_sampler;				//サンプラー
};