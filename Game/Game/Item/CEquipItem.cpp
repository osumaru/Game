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
	swprintf(ItemStatus[1].ItemName, L"“º‚ÌŒ•");
	swprintf(ItemStatus[2].ItemName, L"“S‚ÌŒ•");
	swprintf(ItemStatus[3].ItemName, L"|‚ÌŒ•");
	swprintf(ItemStatus[4].ItemName, L"‰¤‰Æ‚ÌŒ•");
	for (int num = 0;num < 5;num++)
	{
		ItemStatus[num].ItemID = num + 1;
		ItemStatus[num].Itemprice = num + 1 * 10;
		ItemStatus[num].ItemEffect = num + 1 * 5;
		ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
		ItemStatus[num].ItemType = EnInventoryItemType::Equip;
		m_equipItemStatusList.push_back(ItemStatus[num]);
	}

	return true;
}

void CEquipItem::Update()
{

}
