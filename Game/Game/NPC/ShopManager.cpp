#include "stdafx.h"
#include "ShopManager.h"
#include "Shop/ItemShop.h"
#include "Shop/WeaponShop.h"
#include "Shop/NormalShop.h"
#include "IShop.h"

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
		itemshop->Init(position, rotation, shopnum);
		m_shoplist.push_back(itemshop);
		break;
	}
	case enWeaponShop:
	{
		CWeaponShop* weaponshop = New<CWeaponShop>(PRIORITY_SHOP);
		weaponshop->Init(position, rotation, shopnum);
		m_shoplist.push_back(weaponshop);
		break;
	}
	case enNormalNpc:
		CNormalShop* normalshop = New<CNormalShop>(PRIORITY_SHOP);
		normalshop->Init(position, rotation, shopnum);
		m_shoplist.push_back(normalshop);
		break;
	}
}

void CShopManager::Update()
{
	
}