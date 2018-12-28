#include "stdafx.h"
#include "WeaponManager.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../../UI/Menu/EquipInventory.h"
#include "../Weapon/IWeapon.h"
#include "../Weapon/Bow.h"
#include "../Weapon/LongSword.h"
#include "../Weapon/TwinSword.h"
#include "../Weapon/Sword.h"
#include "../../Item/InventoryItem/InventorySword.h"
#include "../../Item/InventoryItem/InventoryLargeSword.h"
#include "../../Item/InventoryItem/InventoryBow.h"
#include "../../Item/InventoryItem/InventoryTwinSword.h"

SWeaponStatus CWeaponManager::m_weaponStatus;

void CWeaponManager::Init(CPlayer* player)
{
	for (int i = 0; i < enWeaponNum; i++)
	{
		std::unique_ptr<IWeapon> ptr;
		std::unique_ptr<IInventoryEquip> equipPtr;
		//SWeaponStatus weaponStatus;
		switch (i)
		{
		case enWeaponLongSword:
			ptr = std::make_unique<CLongSword>();
			equipPtr = std::make_unique<CInventoryLargeSword>();
			m_weaponStatus.attack = 20;
			m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
			break;
		case enWeaponTwinSword:
			ptr = std::make_unique<CTwinSword>();
			equipPtr = std::make_unique<CInventoryTwinSword>();
			m_weaponStatus.attack = 5;
			m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
			break;
		case enWeaponArrow:
			ptr = std::make_unique<CBow>();
			equipPtr = std::make_unique<CInventoryBow>();
			m_weaponStatus.attack = 1;
			m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
			break;
		case enWeaponSword:
			ptr = std::make_unique<CSword>();
			equipPtr = std::make_unique<CInventorySword>();
			m_weaponStatus.attack = 10;
			m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
			break;
		}
		m_weapons[i] = std::move(ptr);
		m_weapons[i]->Init(player);
		m_equipWeapon[i] = std::move(equipPtr);
		m_equipWeapon[i]->Init();
		m_equipWeapon[i]->SetEquipStatus(m_weaponStatus);
 	}
	m_weaponTrace.Init();
}


void CWeaponManager::Update()
{
	if (!m_isAttack) {
		if (Pad().IsTriggerButton(enButtonUp))
		{
			m_weaponState = enWeaponSword;
		}
		else if (Pad().IsTriggerButton(enButtonDown))
		{
			m_weaponState = enWeaponArrow;
		}
		else if (Pad().IsTriggerButton(enButtonLeft))
		{
			m_weaponState = enWeaponTwinSword;
		}
		else if (Pad().IsTriggerButton(enButtonRight))
		{
			m_weaponState = enWeaponLongSword;
		}
	}
	m_weapons[m_weaponState]->Updater();
}

void CWeaponManager::Draw()
{

	m_weapons[m_weaponState]->Drawer();
}

void CWeaponManager::AfterDraw()
{
	if (m_isAttack && m_isTraceDraw)
	{
		m_weaponTrace.Draw();
	}
	m_weapons[m_weaponState]->AfterDrawer();
}

void CWeaponManager::ChangeEquipWeapon(std::unique_ptr<IInventoryEquip> equipWeapon, EnPlayerWeapon weaponNum)
{
	//現在装備中の武器を一時的に保存する
	std::unique_ptr<IInventoryEquip> changeEquip = std::move(m_equipWeapon[weaponNum]);
	//変更したい武器を装備中の武器に設定する
	m_equipWeapon[weaponNum] = std::move(equipWeapon);
	//保存していた武器をインベントリに追加する
	CEquipInventory::AddEquipList(std::move(changeEquip));
}
