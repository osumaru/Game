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

	//描画し終わったかを取得
	bool GetIsDrawEnd()
	{
		return m_isDrawEnd;
	}

private:
	CSprite		m_window;				//ウィンドウ
	CSprite		m_message;				//メッセージ
	CVector2	m_windowSize;			//ウィンドウのサイズ
	float		m_timer = 0.0f;			//タイマー
	bool		m_isDrawEnd = false;	//描画し終わったか
};