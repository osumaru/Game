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
	swprintf(ItemStatus[1].ItemName, L"���̌�");
	swprintf(ItemStatus[2].ItemName, L"�S�̌�");
	swprintf(ItemStatus[3].ItemName, L"�|�̌�");
	swprintf(ItemStatus[4].ItemName, L"���Ƃ̌�");
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
