/*
*	アイテムインベントリクラス
*/
#pragma once
#include "../../Player/ItemList.h"

class CMenu;
class IInventoryItem;

class CItemInventory : public IGameObject
{
public:
	//コンストラクタ
	CItemInventory();

	//デストラクタ
	~CItemInventory();

	//初期化
	//menu	メニューのポインタ
	void Init(CMenu* menu);

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	//カーソル移動
	void PointerMove();

	//アイテムを使用する
	void UseItem();

	//アイテムを捨てる
	void Erase();

private:
	CMenu*				m_menu = nullptr;			//メニュー
	CSprite				m_headline;					//項目
	CSprite				m_backGround;				//背景
	CSprite				m_inventoryWindow;			//インベントリウィンドウ
	CSprite				m_pointer;					//カーソル
	CSprite				m_itemFrame[CItemList::m_itemLimit];	//インベントリの枠
	CSprite				m_itemWindow;				//アイテムウィンドウ
	CSprite				m_buttonBackground;			//ボタン背景
	CSprite				m_buttonA;					//Aボタン
	CSprite				m_buttonB;					//Bボタン
	CSprite				m_buttonY;					//Yボタン
	CSprite				m_buttonAMoji;				//Aボタン文字
	CSprite				m_buttonBMoji;				//Bボタン文字
	CSprite				m_buttonYMoji;				//Yボタン文字
	CFont				m_itemName;					//アイテムの名前
	CVector2			m_basePos = CVector2::Zero;	//初期座標
	CVector2			m_size = CVector2::Zero;	//初期サイズ
	int					m_width = 0;				//インベントリの幅
	int					m_height = 0;				//インベントリの高さ
	int					m_pointerNum = 0;			//カーソルで選んでいるアイテムの番号
};