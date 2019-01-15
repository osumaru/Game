#include "InventoryTwinSword.h"

void CInventoryTwinSword::Init(const wchar_t* itemName, const wchar_t* textureFileName)
{
	m_itemName = itemName;
	m_textureFileName = textureFileName;
	CTexture* texture = TextureResource().LoadTexture(textureFileName);
	m_itemSprite.Init(texture);
}

void CInventoryTwinSword::Draw()
{
	m_itemSprite.Draw();
}
