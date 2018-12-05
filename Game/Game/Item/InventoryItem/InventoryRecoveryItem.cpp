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

bool CInventoryRecoveryItem::Use()
{
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	int playerHP = playerStatus.Health;
	int playerHPMax = playerStatus.MaxHealth;
	//プレイヤーのHPと最大HPを比較する
	if (playerHP < playerHPMax)
	{
		//プレイヤーのHPを回復させる
		GetPlayer().RecoveryHP(m_recoveryValue);
		delete this;
		return true;
	}
	return false;
}
