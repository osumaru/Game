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
	//�Ў茕�̏�����
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
		swprintf(ItemStatus[4].ItemName, L"���@�̌�");
		ItemStatus[4].Itemprice = 1500;
		ItemStatus[4].ItemEffect = 250;
		ItemStatus[4].WeaponType = EnWeaponType::enSword;
		swprintf(ItemStatus[5].ItemName, L"�����O�\�[�h ");
		ItemStatus[5].Itemprice = 200;
		ItemStatus[5].ItemEffect = 35;
		ItemStatus[5].WeaponType = EnWeaponType::enSword;
		swprintf(ItemStatus[6].ItemName, L"�o�C�L���O�\�[�h");
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

		swprintf(ItemStatus[9].ItemName, L"�p�Y�̌�");
		ItemStatus[9].Itemprice = 999;
		ItemStatus[9].ItemEffect = 999;
		ItemStatus[9].WeaponType = EnWeaponType::enSword;
		;

		for (int num = 0;num < 10 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			ItemStatus[num].ItemType = EnInventoryItemType::Equip;
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}

	//����̏�����
	{
		swprintf(ItemStatus[10].ItemName, L"�O���[�g�\�[�h");
		ItemStatus[10].Itemprice = 500;
		ItemStatus[10].ItemEffect = 70;
		ItemStatus[10].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[11].ItemName, L"�o�X�^�[�\�[�h");
		ItemStatus[11].Itemprice = 700;
		ItemStatus[11].ItemEffect = 120;
		ItemStatus[11].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[12].ItemName, L"�N���C���A");
		ItemStatus[12].Itemprice = 600;
		ItemStatus[12].ItemEffect = 90;
		ItemStatus[12].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[13].ItemName, L"�c���@�C�n���_�[");
		ItemStatus[13].Itemprice = 650;
		ItemStatus[13].ItemEffect = 100;
		ItemStatus[13].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[14].ItemName, L"�R�m�̑匕");
		ItemStatus[14].Itemprice = 700;
		ItemStatus[14].ItemEffect = 130;
		ItemStatus[14].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[15].ItemName, L"���̑匕");
		ItemStatus[15].Itemprice = 1200;
		ItemStatus[15].ItemEffect = 180;
		ItemStatus[15].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[16].ItemName, L"�X�̑匕");
		ItemStatus[16].Itemprice = 1200;
		ItemStatus[16].ItemEffect = 180;
		ItemStatus[16].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[17].ItemName, L"���̑匕");
		ItemStatus[17].Itemprice = 1200;
		ItemStatus[17].ItemEffect = 180;
		ItemStatus[17].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[18].ItemName, L"�ۑ�");
		ItemStatus[18].Itemprice = 10;
		ItemStatus[18].ItemEffect = 20;
		ItemStatus[18].WeaponType = EnWeaponType::enLongSword;
		swprintf(ItemStatus[19].ItemName, L"�p�Y�̑匕");
		ItemStatus[19].Itemprice = 9999;
		ItemStatus[19].ItemEffect = 999;
		ItemStatus[19].WeaponType = EnWeaponType::enLongSword;

		for (int num = 10;num < 20 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			ItemStatus[num].ItemType = EnInventoryItemType::Equip;
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}

	return true;
}

void CEquipItem::Update()
{

}
