#include "stdafx.h"
#include "QuickItem.h"


CQuickItem::CQuickItem()
{
}


CQuickItem::~CQuickItem()
{
}

bool CQuickItem::Start()
{
	swprintf(ItemStatus[0].ItemName, L"回復薬（小）");
	ItemStatus[0].Itemprice = 20;
	ItemStatus[0].ItemEffect = 30;
	ItemStatus[0].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[0].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[1].ItemName, L"回復薬（中）");
	ItemStatus[1].Itemprice = 60;
	ItemStatus[1].ItemEffect = 120;
	ItemStatus[1].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[1].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[2].ItemName, L"回復薬（大）");
	ItemStatus[2].Itemprice = 150;
	ItemStatus[2].ItemEffect = 350;
	ItemStatus[2].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[2].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[3].ItemName, L"力のポーション");
	ItemStatus[3].Itemprice = 60;
	ItemStatus[3].ItemEffect = 15;
	ItemStatus[3].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
	ItemStatus[3].ItemType = EnInventoryItemType::Buff;
	swprintf(ItemStatus[4].ItemName, L"硬化のポーション");
	ItemStatus[4].Itemprice = 60;
	ItemStatus[4].ItemEffect = 15;
	ItemStatus[4].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Defense;
	ItemStatus[4].ItemType = EnInventoryItemType::Buff;
	for (int num = 0;num < MAX_QUICK_ITEM_LIST;num++)
	{
		ItemStatus[num].ItemID = 100 + 1;
		m_quickItemStatusList.push_back(ItemStatus[num]);
	}

	return true;
}

void CQuickItem::Update()
{

}
