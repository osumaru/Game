#include "stdafx.h"
#include "WeaponShop.h"


CWeaponShop::CWeaponShop()
{
}


CWeaponShop::~CWeaponShop()
{
}
void CWeaponShop::Init(const CVector3 position, const CQuaternion rotation)
{
	m_position = position;
	m_rotation = rotation;
	m_skinModel.Load(L"Assets/modelData/U2.cmo", NULL);
}

void CWeaponShop::Update()
{
	ShopUpdate();
}

void CWeaponShop::Draw()
{

}