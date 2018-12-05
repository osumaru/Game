#include "InventoryRecoveryItem.h"
#include "../../Player/Player.h"

void CInventoryRecoveryItem::Init()
{
	m_itemName = L"�񕜖�";
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
	//�v���C���[��HP�ƍő�HP���r����
	if (playerHP < playerHPMax)
	{
		//�v���C���[��HP���񕜂�����
		GetPlayer().RecoveryHP(m_recoveryValue);
		delete this;
		return true;
	}
	return false;
}
