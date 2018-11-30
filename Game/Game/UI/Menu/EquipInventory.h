/*
*	装備インベントリクラス
*/

#pragma once

class CMenu;
class IItem;

#include "../../Player/Weapon/WeaponManager.h"

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

	//アイテムを捨てる
	void Erase();

	//所持装備リストに追加
	//weaponStatus		リストに追加する装備のステータス
	static void AddEquipList(SWeaponStatus& weaponStatus);

	//装備リストをクリアする
	void ClearEquipList();

private:
	//ステータスの数
	enum EnStatusNum {
		enStatus_Hp,		//HP
		enStatus_Attack,	//攻撃力
		enStatus_Defense,	//防御力
		enStatus_Num		//ステータスの数
	};
	//ステータス比較用のフォントの数
	enum EnFontNum {
		enFont_CurrentStatus,	//現在のステータス
		enFont_ChangeStatus,	//変更したステータス
		enFont_StatusNum		//ステータスの数
	};

	static const int					m_equipLimit = 15;								//装備所持上限
	CMenu*								m_menu = nullptr;								//メニュー
	CFont								m_statusFont[enFont_StatusNum][enStatus_Num];	//現在の装備と装備変更時のステータス表示
	CSprite								m_backGround;									//背景
	CTexture							m_backGroundTexture;
	CSprite								m_statusWindow[enFont_StatusNum];				//ステータスウィンドウ
	CSprite								m_right;										//右矢印
	CTexture							m_rightTexture;
	CSprite								m_pointer;										//カーソル
	CTexture							m_pointerTexture;
	CSprite								m_equip[m_equipLimit];							//装備アイコン
	CSprite								m_equipWeapon[enWeaponNum];						//装備武器アイコン
	CSprite								m_equipFrame[enWeaponNum];						//装備武器アイコンの枠
	CVector2							m_basePos = CVector2::Zero;						//初期座標
	CVector2							m_baseSize = CVector2::Zero;					//初期サイズ
	int									m_width = 0;									//インベントリの幅
	int									m_height = 0;									//インベントリの高さ
	int									m_pointerNum = 0;								//カーソルで選んでいるアイテムの番号
};