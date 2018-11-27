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

	//武器の軌跡をリセットする
	void WeaponTraceDrawReset()
	{
		m_weaponTrace.Start();
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

private:
	EnPlayerWeapon				m_weaponState = enWeaponSword;				//現在使ってる武器
	std::list<SWeaponStatus>	m_equipList;								//所持装備のリスト
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];						//武器
	bool						m_isAttack = false;							//攻撃中かのフラグ
	bool						m_isAttackCheck = false;					//当たり判定を取っているかのフラグ
	CWeaponTraceDraw			m_weaponTrace;								//武器の軌跡を描画するためのクラス
};