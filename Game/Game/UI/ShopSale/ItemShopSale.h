#pragma once
//アイテムショップで売却時の画面 
class IShop;
#include "../../Item/ItemList.h"

class CItemShopSale : public IGameObject
{
public:
	void Init();

	void Update()override;

	void PostAfterDraw()override;

private:
	SItemStatus			m_choiceItemStatus;
	CSprite				m_headline;					//項目
	CSprite				m_backGround;				//背景
	CSprite				m_inventoryWindow;			//インベントリウィンドウ
	CSprite				m_pointer;					//カーソル
	CSprite				m_itemFrame[CItemList::m_itemLimit];	//インベントリの枠
	CSprite				m_itemWindow;				//アイテムウィンドウ
	CSprite				m_buttonBackground;			//ボタン背景
	CFont				m_itemName;					//アイテムの名前
	CVector2			m_basePos = CVector2::Zero;	//初期座標
	CVector2			m_size = CVector2::Zero;	//初期サイズ
	int					m_width = 0;				//インベントリの幅
	int					m_height = 0;				//インベントリの高さ
	int					m_pointerNum = 0;			//カーソルで選んでいるアイテムの番号
	CFont				m_money;
};