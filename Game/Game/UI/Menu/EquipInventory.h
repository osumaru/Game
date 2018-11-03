/*
*	装備インベントリクラス
*/

#pragma once

#include "../../Player/Weapon.h"

class CMenu;
class IItem;

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
	void AfterDraw() override;

	//装備所持上限を取得
	static int GetEquipLimit()
	{
		return m_equipLimit;
	}

private:
	static const int					m_equipLimit = 15;				//装備所持上限
	CMenu*								m_menu = nullptr;
	CSprite								m_backGround;					//背景
	CTexture							m_backGroundTexture;
	CSprite								m_pointer;						//カーソル
	CTexture							m_pointerTexture;
	CSprite								m_equip[m_equipLimit];			//装備
	std::list<CWeapon::SWeaponStatus>	m_equipList;	//装備リスト
	CVector2							m_basePos = CVector2::Zero;		//初期座標
	CVector2							m_size = CVector2::Zero;		//初期サイズ
	int									m_width = 0;					//インベントリの幅
	int									m_height = 0;					//インベントリの高さ
	int									m_pointerNum = 0;				//カーソルで選んでいるアイテムの番号
};