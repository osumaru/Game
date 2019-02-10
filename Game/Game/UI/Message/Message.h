#pragma once

class CMessage : public IGameObject
{
public:
	//初期化
	//windowSize	ウィンドウサイズ
	//textureName	テクスチャの名前
	void Init(CVector2 windowSize, wchar_t* textureName);

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	//透明から不透明にする速度を設定
	//alphaSpeed	透明から不透明にする速度
	void SetAlphaSpeed(float alphaSpeed)
	{
		m_alphaSpeed = alphaSpeed;
	}

private:
	CSprite		m_window;				//ウィンドウ
	CSprite		m_message;				//メッセージ
	float		m_timer = 0.0f;			//タイマー
	float		m_alphaSpeed = 1.0f;	//透明から不透明にする速度
};