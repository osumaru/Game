#include "InventoryTwinSword.h"

void CInventoryTwinSword::Init(const wchar_t* itemName, const wchar_t* textureFilePath)
{
	m_itemName = itemName;
	m_textureFilePath = textureFilePath;
	CTexture* texture = TextureResource().LoadTexture(textureFilePath);
	m_itemSprite.Init(texture);
}

void CInventoryTwinSword::Draw()
{
	m_itemSprite.Draw();
}
