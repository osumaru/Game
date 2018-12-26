#include "InventoryTwinSword.h"

void CInventoryTwinSword::Init()
{
	m_itemName = L"�o��";
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
	m_itemSprite.Init(texture);
}

void CInventoryTwinSword::Draw()
{
	m_itemSprite.Draw();
}
