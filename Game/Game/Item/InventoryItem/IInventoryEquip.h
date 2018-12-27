#pragma once

#include "../../Player/Weapon/WeaponCommon.h"

class IInventoryEquip 
{
public:
	//コンストラクタ
	IInventoryEquip() {};

	//デストラクタ
	virtual ~IInventoryEquip() {};

	//初期化
	virtual void Init() {};

	//描画
	virtual void Draw() {};

	//アイテムのスプライトを取得
	CSprite* GetSprite()
	{
		return &m_itemSprite;
	}

	//アイテムの名前を取得
	wchar_t* GetItemName()
	{
		return m_itemName;
	}

	//装備のステータスを設定
	void SetEquipStatus(SWeaponStatus equipStatus)
	{
		m_equipStatus = equipStatus;
	}

	//装備のステータスを取得
	SWeaponStatus GetEquipStatus()
	{
		return m_equipStatus;
	}

protected:
	CSprite					m_itemSprite;			//アイテムのスプライト
	wchar_t*				m_itemName;				//アイテムの名前
	SWeaponStatus			m_equipStatus;			//装備のステータス
};