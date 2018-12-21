#pragma once
#include "IWeapon.h"
#include "WeaponCommon.h"

class CPlayer;
//武器を管理するクラス

class CWeaponManager
{
public:

	void Init(CPlayer* player);

	void Update();

	void Draw();

	void AfterDraw();

	//現在使っている武器の種類を取得
	EnPlayerWeapon GetCurrentState() const
	{
		return m_weaponState;
	}

	/*
	武器のステータスを取得
	weaponNum	武器の種類
	*/
	SWeaponStatus& GetWeaponStatus(EnPlayerWeapon weaponNum)
	{
		return m_weapons[weaponNum]->GetWeaponStatus();
	}

	/*
	武器を取得
	weaponNum		武器の種類
	*/
	IWeapon* GetWeapon(EnPlayerWeapon weaponNum)
	{
		return m_weapons[weaponNum].get();
	}


	/*
	現在装備している武器を取得
	*/
	IWeapon* GetWeapon()
	{
		return m_weapons[m_weaponState].get();
	}

	//攻撃しているかのフラグを取得
	bool GetIsAttack()
	{
		return m_isAttack;
	}

	//攻撃しているかのフラグを設定
	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
	}

	//当たり判定を取っているかのフラグを取得。
	bool GetIsAttackCheck()
	{
		return m_isAttackCheck;
	}

	//当たり判定を取っているかのフラグを設定
	void SetIsAttackCheck(bool isAttack)
	{
		m_isAttackCheck = isAttack;
	}

	CWeaponTraceDraw& GetWeaponTraceDraw()
	{
		return m_weaponTrace;
	}

	void SetIsTraceDraw(bool isTraceDraw)
	{
		m_isTraceDraw = isTraceDraw;
	}

private:
	EnPlayerWeapon				m_weaponState = enWeaponSword;				//現在使ってる武器
	std::list<SWeaponStatus>	m_equipList;								//所持装備のリスト
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];						//武器
	bool						m_isAttack = false;							//攻撃中かのフラグ
	bool						m_isAttackCheck = false;					//当たり判定を取っているかのフラグ
	CWeaponTraceDraw			m_weaponTrace;								//武器の軌跡を描画するためのクラス
	bool						m_isTraceDraw = false;
};