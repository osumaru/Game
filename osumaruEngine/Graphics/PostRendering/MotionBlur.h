#pragma once

class CMotionBlur : Uncopyable
{
public:

	void Init();

	void Update();

	void Draw();

private:
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	bool				m_isActive = false;		//アクティブかどうかのフラグ
	static const int	BLUR_RANGE = 8;		//ブラーをかける範囲
	static const int	DOWN_SAMPLING_NUM = 5;	//ダウンサンプリングの数
	CPrimitive			m_primitive;			//プリミティブ
	CShader				m_vs;					//頂点シェーダー
	CShader				m_ps;					//ピクセルシェーダー
	CSamplerState		m_sampler;				//サンプラー
};