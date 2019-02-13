/*
*	装備インベントリクラス
*/

#pragma once

class CMenu;
class IItem;
class IInventoryEquip;
#include "../../Player/Weapon/WeaponCommon.h"
#include "../../Item/EquipList.h"

class CEquipInventory : public IGameObject
{
public:
	//コンストラクタ
	CEquipInventory();

	//デストラクタ
	~CEquipInventory();

	//初期化
	//menu		メニューのポインタ
	void Init(CMenu* menu);

	//更新される前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	//装備リストの整理する
	void EquipListReset();

	//カーソル移動
	void PointerMove();

	//装備する
	void Equip();

	//ステータス計算
	void CalucStatus();

	//アイテムを捨てる
	void Erase();

	//ステータスの数
	enum EnStatusNum
	{
		enStatus_Hp,		//HP
		enStatus_Attack,	//攻撃力
		enStatus_Defense,	//防御力
		enStatus_Num		//ステータスの数
	};

private:

	//ステータス比較用のフォントの数
	enum EnFontNum {
		enFont_CurrentStatus,	//現在のステータス
		enFont_ChangeStatus,	//変更したステータス
		enFont_StatusNum		//ステータスの数
	};
	CMenu*			 m_menu = nullptr;								//メニュー
	CSprite			 m_headline;									//項目
	CSprite			 m_background;									//背景
	CSprite			 m_inventoryWindow;								//インベントリウィンドウ
	CSprite			 m_statusWindow[enFont_StatusNum];				//ステータスウィンドウ
	CSprite			 m_right;										//右矢印
	CSprite			 m_pointer;										//カーソル
	CSprite			 m_frame[CEquipList::m_equipLimit];							//インベントリの枠
	CSprite			 m_equipWeapon[enWeaponNum];					//装備武器アイコン
	CSprite			 m_equipFrame[enWeaponNum];						//装備武器アイコンの枠
	CSprite			 m_buttonBackground;							//ボタン背景
	CSprite			 m_buttonA;										//Aボタン
	CSprite			 m_buttonB;										//Bボタン
	CSprite			 m_buttonY;										//Yボタン
	CSprite			 m_buttonAMoji;									//Aボタン文字
	CSprite			 m_buttonBMoji;									//Bボタン文字
	CSprite			 m_buttonYMoji;									//Yボタン文字
	CFont			 m_equipName[enFont_StatusNum];					//装備の名前
	CFont			 m_statusFont[enFont_StatusNum][enStatus_Num];	//現在の装備と装備変更時のステータス文字
	CFont			 m_statusFontNum[enFont_StatusNum][enStatus_Num];//現在の装備と装備変更時のステータス数値
	CVector2		 m_basePos = CVector2::Zero;					//初期座標
	CVector2		 m_baseSize = CVector2::Zero;					//初期サイズ
	int				 m_width = 0;									//インベントリの幅
	int				 m_height = 0;									//インベントリの高さ
	int				 m_pointerNum = 0;								//カーソルで選んでいるアイテムの番号
};