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
	for (IShop* shopNpc : m_shoplist)
	{
		Delete(shopNpc);
	}
	m_shoplist.clear();
}

void CShopManager::InitShop(const CVector3 position, const CQuaternion rotation, const EShop shopnum)
{
	switch (shopnum)
	{
	case enItemShop:
	{
		CItemShop* itemshop = New<CItemShop>(PRIORITY_SHOP);
		itemshop->Init(position, rotation);
		m_shoplist.push_back(itemshop);
		break;
	}
	case enWeaponShop:
	{
		CWeaponShop* weaponshop = New<CWeaponShop>(PRIORITY_SHOP);
		weaponshop->Init(position, rotation);
		m_shoplist.push_back(weaponshop);
		break;
	}
	}
}

void CShopManager::Update()
{
	
}