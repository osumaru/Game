#include "InventoryBow.h"

void CInventoryBow::Init()
{
	m_itemName = L"‹|";
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
	m_itemSprite.Init(texture);
}

void CInventoryBow::Draw()
{
	m_itemSprite.Draw();
}
