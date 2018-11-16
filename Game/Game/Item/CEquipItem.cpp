#include "stdafx.h"
#include "CEquipItem.h"


CEquipItem::CEquipItem()
{
}


CEquipItem::~CEquipItem()
{
}


//Œã‚Åƒf[ƒ^‚©‚ç“Ç‚İ‚Ü‚·
bool CEquipItem::Start()
{
	swprintf(ItemStatus[0].ItemName, L"ƒqƒmƒL‚ÌŒ•");
	ItemStatus[0].Itemprice = 10;
	ItemStatus[0].ItemEffect = 5;
	swprintf(ItemStatus[1].ItemName, L"“º‚ÌŒ•");
	ItemStatus[1].Itemprice = 50;
	ItemStatus[1].ItemEffect = 10;
	swprintf(ItemStatus[2].ItemName, L"“S‚ÌŒ•");
	ItemStatus[2].Itemprice = 100;
	ItemStatus[2].ItemEffect = 25;
	swprintf(ItemStatus[3].ItemName, L"|‚ÌŒ•");
	ItemStatus[3].Itemprice = 250;
	ItemStatus[3].ItemEffect = 40;
	swprintf(ItemStatus[4].ItemName, L"‰¤‰Æ‚ÌŒ•");
	ItemStatus[4].Itemprice = 1500;
	ItemStatus[4].ItemEffect = 75;
	for (int num = 0;num < 5;num++)
	{
		ItemStatus[num].ItemID = num + 1;
		ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
		ItemStatus[num].ItemType = EnInventoryItemType::Equip;
		m_equipItemStatusList.push_back(ItemStatus[num]);
	}

	return true;
}

void CEquipItem::Update()
{

}
