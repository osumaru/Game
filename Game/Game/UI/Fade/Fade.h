#pragma once
class CFade : public IGameObject
{
public:
	CFade();
	~CFade();
	bool Start();
	void Update();
	void AfterDraw();
	void FadeOut(); //フェイドアウトを行うためにを呼び出すための関数
	void FadeIn();	//フェイドインを行うために呼び出される関数
	//実行中かどうかを返す
	bool IsExecute()
	{
		return m_isExecute;
	}

private:
	enum EnFadeState
	{
		enFadeOut,
		enFadeIn,
	};

	CSprite			m_fadeSprite;							//スプライト
	CTexture		m_fadeTexture;							//テクスチャ
	float			m_texturerAlpha = 0.0f;
	CVector2		m_texturePosition = { 0.0f,0.0f };
	CVector2		m_textureSize = { 1280,720 };

	float			m_fadeTime = 0.0f;
	bool            m_isExecute = false;					//実行中かどうか
	EnFadeState		m_fadeState = enFadeOut;
	const float		FADE_OUT_TIME = 2.0f;					//フェイドアウトするまでの時間
	const float		FADE_IN_TIME = 2.0f;					//フェイドインするまでの時間

};

