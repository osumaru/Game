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

void CWeaponManager::Init(CPlayer* player)
{
	for (int i = 0; i < enWeaponNum; i++)
	{
		std::unique_ptr<IWeapon> ptr;
		switch (i)
		{
		case enWeaponLongSword:
			ptr = std::make_unique<CLongSword>();
			break;
		case enWeaponTwinSword:
			ptr = std::make_unique<CTwinSword>();
			break;
		case enWeaponArrow:
			ptr = std::make_unique<CBow>();
			break;
		case enWeaponSword:
			ptr = std::make_unique<CSword>();
			break;
		}
		m_weapons[i] = std::move(ptr);
		m_weapons[i]->Init(player);

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
	if (m_isAttack)
	{
		m_weaponTrace.Draw();
	}
	m_weapons[m_weaponState]->AfterDrawer();
}