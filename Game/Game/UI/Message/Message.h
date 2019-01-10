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
	void AfterDraw() override;
private:
	CSprite m_window;	//ウィンドウ
	CSprite	m_message;	//メッセージ
};