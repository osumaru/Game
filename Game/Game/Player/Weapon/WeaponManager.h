#pragma once
#include "IWeapon.h"

class CPlayer;
//武器を管理するクラス

class CWeaponManager
{
public:
	enum EnPlayerWeapon
	{
		enSword,			//片手剣
		enLongSword,		//両手剣
		enArrow,				//弓矢
		enTwinSword,		//二刀
		enWeaponNum,
		enInvalid			//何もない
	};

	void Init(CPlayer* player);

	void Update();

	void Draw();

	void AfterDraw();

	EnPlayerWeapon GetCurrentState() const
	{
		return m_weaponState;
	}

	struct SWeaponStatus
	{
		int attack = 0;
		int diffence = 0;
		EnPlayerWeapon weaponNum = enInvalid;
	};

	//所持装備リストに追加
	//item		装備リストに追加するアイテム
	void AddEquipList(SWeaponStatus& item);

	//装備の変更
	//number		変更したい装備の番号
	void ChangeEquip(int number);

	//所持装備リストを取得
	std::list<SWeaponStatus>& GetEquipList()
	{
		return m_equipList;
	}

	/*
	武器のステータスを取得
	weaponNum	武器の種類
	*/
	SWeaponStatus& GetWeaponStatus(EnPlayerWeapon weaponNum)
	{
		return m_equipWeapon[weaponNum];
	}

	IWeapon* GetWeapon(EnPlayerWeapon weaponNum)
	{
		return m_weapons[weaponNum].get();
	}
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
	}

	bool GetIsAttackCheck()
	{
		return m_isAttackCheck;
	}

	void SetIsAttackCheck(bool isAttack)
	{
		m_isAttackCheck = isAttack;
	}

private:
	CPlayer*					m_pPlayer = nullptr;						//プレイヤーのインスタンス
	EnPlayerWeapon				m_weaponState = EnPlayerWeapon::enSword;	//現在使ってる武器
	std::list<SWeaponStatus>	m_equipList;								//所持装備のリスト
	SWeaponStatus				m_equipWeapon[enWeaponNum];		//装備中の武器ノステータス
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];
	bool						m_isAttack = false;
	bool						m_isAttackCheck = false;
};