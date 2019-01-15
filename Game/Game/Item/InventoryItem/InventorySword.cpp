#include "InventorySword.h"

void CInventorySword::Init(const wchar_t* itemName, const wchar_t* textureFileName)
{
	m_itemName = itemName;
	m_textureFileName = textureFileName;
	CTexture* texture = TextureResource().LoadTexture(textureFileName);
	m_itemSprite.Init(texture);
}

void CInventorySword::Draw()
{
	m_itemSprite.Draw();
}