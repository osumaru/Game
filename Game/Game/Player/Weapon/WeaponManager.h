#pragma once
#include "IWeapon.h"
#include "WeaponCommon.h"
#include "../../Item/InventoryItem/IInventoryEquip.h"

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

	//装備中の武器を取得
	//weaponNum		武器の種類
	IInventoryEquip* GetEquipWeapon(EnPlayerWeapon weaponNum)
	{
		return m_equipWeapon[weaponNum].get();
	}

	//装備中の武器を取得
	IInventoryEquip* GetEquipWeapon()
	{
		return m_equipWeapon[m_weaponState].get();
	}

	/////////削除するかも/////////
	//装備する武器を設定
	//equipWeapon	変更したい武器
	//weaponNum		武器の種類
	void SetEquipWeapon(std::unique_ptr<IInventoryEquip> equipWeapon, EnPlayerWeapon weaponNum)
	{
		m_equipWeapon[weaponNum] = std::move(equipWeapon);
	}

	//装備している武器を交換する
	//equipWeapon	変更したい武器
	//weaponNum		武器の種類
	void ChangeEquipWeapon(std::unique_ptr<IInventoryEquip> equipWeapon, EnPlayerWeapon weaponNum);

private:
	EnPlayerWeapon				m_weaponState = enWeaponSword;				//現在使ってる武器
	std::unique_ptr<IInventoryEquip> m_equipWeapon[enWeaponNum];			//装備中の武器
	std::unique_ptr<IWeapon>	m_weapons[enWeaponNum];						//武器
	bool						m_isAttack = false;							//攻撃中かのフラグ
	bool						m_isAttackCheck = false;					//当たり判定を取っているかのフラグ
	CWeaponTraceDraw			m_weaponTrace;								//武器の軌跡を描画するためのクラス
	bool						m_isTraceDraw = false;
};