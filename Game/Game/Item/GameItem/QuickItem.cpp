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
	swprintf(ItemStatus[0].ItemName, L"回復薬（極小）");
	ItemStatus[0].Itemprice = 100;
	ItemStatus[0].ItemEffect = 10;
	ItemStatus[0].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[0].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[0].ItemSprite, L"Assets/sprite/Item/quick/Item_104.png");

	swprintf(ItemStatus[1].ItemName, L"回復薬（小）");
	ItemStatus[1].Itemprice = 400;
	ItemStatus[1].ItemEffect = 25;
	ItemStatus[1].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[1].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[1].ItemSprite,L"Assets/sprite/Item/quick/Item_101.png");

	swprintf(ItemStatus[2].ItemName, L"回復薬（中）");
	ItemStatus[2].Itemprice = 1500;
	ItemStatus[2].ItemEffect = 50;
	ItemStatus[2].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[2].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[2].ItemSprite, L"Assets/sprite/Item/quick/Item_102.png");

	swprintf(ItemStatus[3].ItemName, L"回復薬（大）");
	ItemStatus[3].Itemprice = 3200;
	ItemStatus[3].ItemEffect = 80;
	ItemStatus[3].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[3].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[3].ItemSprite, L"Assets/sprite/Item/quick/Item_103.png");

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
