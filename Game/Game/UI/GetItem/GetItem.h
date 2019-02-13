/*
*	アイテムを拾うUIクラス
*/

#pragma once
#include "GetItemName.h"

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
	CGetItemName* GetCGetItemName()
	{
		return &m_itemName;
	}


private:
	CSprite m_aButton;			//Aボタン
	CSprite m_pickUp;			//拾う
	CSprite	m_back;				//背景
	int		m_drawCount = 0;	//描画するかを決めるカウント。0なら描画しない
	CGetItemName	m_itemName;
};