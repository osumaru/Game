/*
*	アイテムを拾うUIクラス
*/

#pragma once

class CGetItem : public IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	//描画カウントを増やす
	void AddDrawCount()
	{
		m_drawCount++;
	}

	//描画カウントを減らす
	void SubtractDrawCount()
	{
		m_drawCount--;
	}
	void ItemeNameDraw(CTexture* texture,wchar_t* ItemName )
	{
		m_isDrawItemName = true;
		m_sprite[1].Init(texture);
		m_sprite[1].SetSize({ 80,80.0f });
		m_sprite[1].SetPosition({ -200.0f,-250.0f });
		m_font.SetString(ItemName);
	}
	void NoItemeNameDraw()
	{
		m_isDrawItemName = false;
	}

private:
	CSprite m_aButton;			//Aボタン
	CSprite m_pickUp;			//拾う
	CSprite	m_back;				//背景
	int		m_drawCount = 0;	//描画するかを決めるカウント。0なら描画しない
	CSprite								m_sprite[2];
	CFont								m_font;
	bool								m_isDrawItemName = false;
};