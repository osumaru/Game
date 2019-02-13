/*
*	獲得したアイテムを表示するクラス
*/

#pragma once

class CGetItemName : public IGameObject
{
public:
	//初期化
	//texture	テクスチャ
	//itemName	アイテムの名前
	void Init();

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	void SetIteName(CTexture* texture, wchar_t* itemName);
private:
	CSprite	m_sprite[2];
	CFont	m_font;
	float	m_drawTime = 0.0f;
	bool	m_isDraw = false;
};