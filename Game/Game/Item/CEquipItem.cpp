#include "stdafx.h"
#include "CEquipItem.h"


CEquipItem::CEquipItem()
{
}


CEquipItem::~CEquipItem()
{
}


//��Ńf�[�^����ǂݍ��܂�
bool CEquipItem::Start()
{
	swprintf(ItemStatus[0].ItemName, L"�q�m�L�̌�");
	ItemStatus[0].Itemprice = 10;
	ItemStatus[0].ItemEffect = 5;
	swprintf(ItemStatus[1].ItemName, L"���̌�");
	ItemStatus[1].Itemprice = 50;
	ItemStatus[1].ItemEffect = 10;
	swprintf(ItemStatus[2].ItemName, L"�S�̌�");
	ItemStatus[2].Itemprice = 100;
	ItemStatus[2].ItemEffect = 25;
	swprintf(ItemStatus[3].ItemName, L"�|�̌�");
	ItemStatus[3].Itemprice = 250;
	ItemStatus[3].ItemEffect = 40;
	swprintf(ItemStatus[4].ItemName, L"���Ƃ̌�");
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
