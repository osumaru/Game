#include "stdafx.h"
#include "ShopManager.h"


CShopManager::CShopManager()
{
}


CShopManager::~CShopManager()
{
	
}

void CShopManager::DeleteList()
{
	for (IShop* shopNpc : m_npclist)
	{
		Delete(shopNpc);
	}
	m_npclist.clear();
}

void CShopManager::InitShop(const CVector3 position, const CQuaternion rotation, const EShop shopnum)
{
	switch (shopnum)
	{
	case enItemShop:
	{
		CItemShop* itemshop = New<CItemShop>(PRIORITY_NPC);
		itemshop->Init(position, rotation);
		m_npclist.push_back(itemshop);
		break;
	}
	case enWeaponShop:
	{
		CWeaponShop* weaponshop = New<CWeaponShop>(PRIORITY_NPC);
		weaponshop->Init(position, rotation);
		m_npclist.push_back(weaponshop);
		break;
	}
	}
}

void CShopManager::Update()
{
	
}