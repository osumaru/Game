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
#include "../../Scene/SceneManager.h"

std::unique_ptr<IInventoryEquip> CWeaponManager::m_equipWeapon[enWeaponNum];

void CWeaponManager::Init(CPlayer* player)
{
	if (GetSceneManager().GetIsStart())
	{
		//毎回初期化する変数
		m_isAttack = false;
		m_isAttackCheck = false;
		m_isTraceDraw = false;

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
		for (int i = 0; i < 2; i++)
		{
			m_weaponTrace[i].Init();
		}
	}
	else
	{
		for (int i = 0; i < enWeaponNum; i++)
		{
			std::unique_ptr<IWeapon> ptr;
			std::unique_ptr<IInventoryEquip> equipPtr;
			SWeaponStatus weaponStatus;
			switch (i)
			{
			case enWeaponLongSword:
				ptr = std::make_unique<CLongSword>();
				equipPtr = std::make_unique<CInventoryLargeSword>();
				weaponStatus.attack = 20;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
				break;
			case enWeaponTwinSword:
				ptr = std::make_unique<CTwinSword>();
				equipPtr = std::make_unique<CInventoryTwinSword>();
				weaponStatus.attack = 5;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
				break;
			case enWeaponArrow:
				ptr = std::make_unique<CBow>();
				equipPtr = std::make_unique<CInventoryBow>();
				weaponStatus.attack = 1;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
				break;
			case enWeaponSword:
				ptr = std::make_unique<CSword>();
				equipPtr = std::make_unique<CInventorySword>();
				weaponStatus.attack = 10;
				weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
				break;
			}
			m_weapons[i] = std::move(ptr);
			m_weapons[i]->Init(player);
			m_equipWeapon[i] = std::move(equipPtr);
			m_equipWeapon[i]->Init();
			m_equipWeapon[i]->SetEquipStatus(weaponStatus);
		}
		for (int i = 0; i < 2; i++)
		{
			m_weaponTrace[i].Init();
		}
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

void CWeaponManager::Draw()
{

	m_weapons[m_weaponState]->Drawer();
}

void CWeaponManager::AfterDraw()
{
	if (m_isAttack && m_isTraceDraw)
	{
		for (int i = 0; i < GetWeapon()->GetMaxWeaponHitNum(); i++)
		{
			m_weaponTrace[i].Draw();
		}
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
