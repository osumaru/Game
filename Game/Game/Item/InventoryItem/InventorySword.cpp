#include "InventorySword.h"

void CInventorySword::Init()
{
	m_itemName = L"Œ•";
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
	m_itemSprite.Init(texture);
}

void CInventorySword::Draw()
{
	m_itemSprite.Draw();
}