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

void CWeaponManager::ChangeEquip(int number)
{
	if (!m_equipList.empty())
	{
		//‘I‚ñ‚¾‘•”õ‚ÆŒ»İ‚Ì‘•”õ‚ğŒğŠ·‚·‚é
		std::list<SWeaponStatus>::iterator it;
		it = m_equipList.begin();
		for (int i = 0; i < number; i++)
		{
			it++;
		}
		int weaponNumber = (*it).weaponNum;
		if (m_weapons[weaponNumber]->GetWeaponStatus().weaponNum == enInvalid)
		{
			//‰½‚à‘•”õ‚µ‚Ä‚¢‚È‚¢
			m_weapons[weaponNumber]->SetWeaponStatus(*it);
			m_equipList.erase(it);
		}
		else
		{
			//‘•”õ‚ğŒğŠ·‚·‚é
			SWeaponStatus equipWeapon = m_weapons[weaponNumber]->GetWeaponStatus();
			m_weapons[weaponNumber]->SetWeaponStatus(*it);
			(*it) = equipWeapon;
		}
	}
}

void CWeaponManager::AddEquipList(SWeaponStatus& item)
{
	if (m_equipList.size() < CEquipInventory::GetEquipLimit())
	{
		//ŠãŒÀ‚ğ’´‚¦‚Ä‚¢‚È‚¯‚ê‚Î‘•”õƒŠƒXƒg‚É’Ç‰Á
		m_equipList.push_back(item);
	}
}

void CWeaponManager::Draw()
{
	m_weapons[m_weaponState]->Drawer();
}

void CWeaponManager::AfterDraw()
{
	m_weapons[m_weaponState]->AfterDrawer();
}