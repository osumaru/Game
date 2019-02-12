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
	swprintf(ItemStatus[0].ItemName, L"�񕜖�i���j");
	ItemStatus[0].Itemprice = 400;
	ItemStatus[0].ItemEffect = 20;
	ItemStatus[0].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[0].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[0].ItemSprite,L"Assets/sprite/Item/quick/Item_101.png");

	swprintf(ItemStatus[1].ItemName, L"�񕜖�i���j");
	ItemStatus[1].Itemprice = 1500;
	ItemStatus[1].ItemEffect = 50;
	ItemStatus[1].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[1].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[1].ItemSprite, L"Assets/sprite/Item/quick/Item_102.png");
	swprintf(ItemStatus[2].ItemName, L"�񕜖�i��j");
	ItemStatus[2].Itemprice = 3200;
	ItemStatus[2].ItemEffect = 80;
	ItemStatus[2].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Health;
	ItemStatus[2].ItemType = EnInventoryItemType::Recovery;
	swprintf(ItemStatus[2].ItemSprite, L"Assets/sprite/Item/quick/Item_103.png");

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
