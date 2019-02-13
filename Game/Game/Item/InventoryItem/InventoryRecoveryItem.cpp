#include "InventoryRecoveryItem.h"
#include "../../Player/Player.h"

void CInventoryRecoveryItem::Init()
{
	m_itemName = L"回復薬";
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/Potion/RedPotion.png");
	m_itemSprite.Init(texture);
}

void CInventoryRecoveryItem::Draw()
{
	m_itemSprite.Draw();
}
void CInventoryRecoveryItem::TexUpdate()
{
	m_itemName = m_status.ItemName;
	CTexture* texture = TextureResource().LoadTexture(m_status.ItemSprite);
	m_itemSprite.SetTexture(texture);
}

bool CInventoryRecoveryItem::Use()
{
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	int playerHP = playerStatus.Health;
	int playerHPMax = playerStatus.MaxHealth;
	//プレイヤーのHPと最大HPを比較する
	if (playerHP < playerHPMax)
	{
		//プレイヤーのHPを回復させる
		m_recoveryValue = ((float)m_status.ItemEffect / 100.0f ) * (float)playerHPMax;
		GetPlayer().RecoveryHP((int)m_recoveryValue);
		return true;
	}
	return false;
}
