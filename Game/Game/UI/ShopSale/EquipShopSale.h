/*
*	装備インベントリクラス
*/

#pragma once

class CMenu;
class IItem;
class IInventoryEquip;
#include "../../Player/Weapon/WeaponCommon.h"
#include "../../Item/EquipList.h"

class CEquipShopSale : public IGameObject
{
public:
	//コンストラクタ
	CEquipShopSale();

	//デストラクタ
	~CEquipShopSale();

	//初期化
	void Init();

	//更新
	void Update() override;

	//描画
	void PostAfterDraw() override;

	//装備リストの整理する
	void EquipListReset();

	//カーソル移動
	void PointerMove();

	//アイテムを売却する
	void Sale();

private:
	//ステータスの数
	enum EnStatusNum
	{
		enStatus_Hp,		//HP
		enStatus_Attack,	//攻撃力
		enStatus_Defense,	//防御力
		enStatus_Num		//ステータスの数
	};

	CSprite			 m_headline;									//項目
	CSprite			 m_background;									//背景
	CSprite			 m_inventoryWindow;								//インベントリウィンドウ
	CSprite			 m_statusWindow;				//ステータスウィンドウ
	CSprite			 m_pointer;										//カーソル
	CSprite			 m_frame[CEquipList::m_equipLimit];				//インベントリの枠
	CFont			 m_equipName;									//装備の名前
	CFont			 m_statusFont[enStatus_Num];					//現在の装備と装備変更時のステータス文字
	CFont			 m_statusFontNum[enStatus_Num];					//現在の装備と装備変更時のステータス数値
	CVector2		 m_basePos = CVector2::Zero;					//初期座標
	CVector2		 m_baseSize = CVector2::Zero;					//初期サイズ
	int				 m_width = 0;									//インベントリの幅
	int				 m_height = 0;									//インベントリの高さ
	int				 m_pointerNum = 0;								//カーソルで選んでいるアイテムの番号
	CSoundSource	 m_equipSound[2];
	CFont			m_money;
};