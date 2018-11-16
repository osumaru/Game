/*
*	装備インベントリクラス
*/

#pragma once

class CMenu;
class IItem;

#include "../../Player/Weapon.h"

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

	//装備リストのテクスチャを整理する
	//isInit	テクスチャを初期化するか
	void EquipListReset(bool isInit);

	//カーソル移動
	void PointerMove();

	//装備する
	void Equip();

	//ステータス計算
	void CalucStatus();

	//装備所持上限を取得
	static int GetEquipLimit()
	{
		return m_equipLimit;
	}

private:
	//ステータスの数
	enum EnStatusNum {
		enStatus_Hp,
		enStatus_Attack,
		enStatus_Defense,
		enStatus_Num
	};
	//ステータス比較用のフォントの数
	enum EnFontNum {
		enFont_CurrentStatus,
		enFont_ChangeStatus,
		enFont_StatusNum
	};

	static const int					m_equipLimit = 15;								//装備所持上限
	CMenu*								m_menu = nullptr;
	CFont								m_statusFont[enFont_StatusNum][enStatus_Num];	//現在の装備と装備変更時のステータス表示
	CSprite								m_backGround;									//背景
	CTexture							m_backGroundTexture;
	CSprite								m_statusWindow;									//ステータスウィンドウ
	CTexture							m_statusWindowTexture;							
	CSprite								m_right;										//右矢印
	CTexture							m_rightTexture;
	CSprite								m_pointer;										//カーソル
	CTexture							m_pointerTexture;
	CSprite								m_equip[m_equipLimit];							//装備アイコン
	std::list<CWeapon::SWeaponStatus>	m_equipList;									//装備リスト
	std::list<IItem*>					m_itemEquipList;
	CVector2							m_basePos = CVector2::Zero;						//初期座標
	CVector2							m_baseSize = CVector2::Zero;					//初期サイズ
	int									m_width = 0;									//インベントリの幅
	int									m_height = 0;									//インベントリの高さ
	int									m_pointerNum = 0;								//カーソルで選んでいるアイテムの番号
};