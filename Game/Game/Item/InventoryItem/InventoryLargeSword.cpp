#include "InventoryLargeSword.h"

void CInventoryLargeSword::Init()
{
	m_itemName = L"‘åŒ•";
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
	m_itemSprite.Init(texture);
}

void CInventoryLargeSword::Draw()
{
	m_itemSprite.Draw();
}
