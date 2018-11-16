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
	ItemStatus[0].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[1].ItemName, L"���̌� ");
	ItemStatus[1].Itemprice = 50;
	ItemStatus[1].ItemEffect = 10;
	ItemStatus[1].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[2].ItemName, L"�S�̌� ");
	ItemStatus[2].Itemprice = 100;
	ItemStatus[2].ItemEffect = 25;
	ItemStatus[2].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[3].ItemName, L"�|�̌� ");
	ItemStatus[3].Itemprice = 250;
	ItemStatus[3].ItemEffect = 40;
	ItemStatus[3].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[4].ItemName, L"�G�N�X�J���o�[");
	ItemStatus[4].Itemprice = 1500;
	ItemStatus[4].ItemEffect = 250;
	ItemStatus[4].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[5].ItemName, L"�� ");
	ItemStatus[5].Itemprice = 200;
	ItemStatus[5].ItemEffect = 35;
	ItemStatus[5].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[6].ItemName, L"�N���C���A");
	ItemStatus[6].Itemprice = 500;
	ItemStatus[6].ItemEffect = 60;
	ItemStatus[6].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[7].ItemName, L"�Âт���");
	ItemStatus[7].Itemprice = 100;
	ItemStatus[7].ItemEffect = 5;
	ItemStatus[7].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[8].ItemName, L"�V���[�g�\�[�h");
	ItemStatus[8].Itemprice = 120;
	ItemStatus[8].ItemEffect = 30;
	ItemStatus[8].WeaponType = EnWeaponType::enSword;
	swprintf(ItemStatus[9].ItemName, L"�����O�\�[�h");
	ItemStatus[9].Itemprice = 150;
	ItemStatus[9].ItemEffect = 50;
	ItemStatus[9].WeaponType = EnWeaponType::enLongSword;
	for (int num = 0;num < MAX_ITEM_NUMBER;num++)
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
