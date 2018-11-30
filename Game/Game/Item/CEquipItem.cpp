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
		swprintf(ItemStatus[0].ItemText, L"�q�m�؂ō��ꂽ�،��B\n�q���������D��Ŏg���Ă���B");
		ItemStatus[0].Itemprice = 10;
		ItemStatus[0].ItemEffect = 5;
		ItemStatus[0].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[1].ItemName, L"���̌� ");
		swprintf(ItemStatus[1].ItemText, L"���ō��ꂽ���B\n��g�p�Ƃ��čD���\n�g���Ă���B");
		ItemStatus[1].Itemprice = 50;
		ItemStatus[1].ItemEffect = 10;
		ItemStatus[1].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[2].ItemName, L"�S�̌� ");
		swprintf(ItemStatus[2].ItemText, L"�S�ō��ꂽ���B\n���m��b���A�`���҂�\n���p���Ă���B");
		ItemStatus[2].Itemprice = 100;
		ItemStatus[2].ItemEffect = 75;
		ItemStatus[2].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[3].ItemName, L"�|�̌� ");
		swprintf(ItemStatus[3].ItemText, L"�|�ō��ꂽ���B\n�R�m�╺�����ȂǏ�ʐE�̎�\n�����p���Ă���B");
		ItemStatus[3].Itemprice = 250;
		ItemStatus[3].ItemEffect = 40;
		ItemStatus[3].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[4].ItemName, L"���@�̌�");
		swprintf(ItemStatus[4].ItemText, L"���͂����߂�ꂽ���B\n�ꕔ�̏㗬�K���݂̂�\n�������Ă���B");
		ItemStatus[4].Itemprice = 1500;
		ItemStatus[4].ItemEffect = 250;
		ItemStatus[4].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[5].ItemName, L"�����O�\�[�h ");
		swprintf(ItemStatus[5].ItemText, L"�ʏ�̕Ў茕��蒷�����B\n�n��œG�𓢂��߂�\n���ꂽ�B");
		ItemStatus[5].Itemprice = 550;
		ItemStatus[5].ItemEffect = 110;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[6].ItemName, L"�o�C�L���O�\�[�h");
		swprintf(ItemStatus[6].ItemText, L"���閯�����g�p���Ă������B\n�����̒��ł��㗬�K���̎҂�\n���p���Ă�������B");
		ItemStatus[6].Itemprice = 740;
		ItemStatus[6].ItemEffect = 130;
		ItemStatus[6].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[7].ItemName, L"�Âт���");
		swprintf(ItemStatus[7].ItemText, L"���ѕt�������B\n���Ȃ�̔N�����o���Ă���\n����Ƃ��Ă͂قƂ�ǈӖ����Ȃ��Ȃ��B");
		ItemStatus[7].Itemprice = 1000;
		ItemStatus[7].ItemEffect = 5;
		ItemStatus[7].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[8].ItemName, L"�V���[�g�\�[�h");
		swprintf(ItemStatus[8].ItemText, L"��ʓI�ȕЎ茕�B\n��ɕ��������p���Ă���B");
		ItemStatus[8].Itemprice = 120;
		ItemStatus[8].ItemEffect = 30;
		ItemStatus[8].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[9].ItemName, L"�p�Y�̌�");
		swprintf(ItemStatus[9].ItemText, L"���̉p�Y�݂̂ɑ����錕�B\n��U��œG��j�邱�Ƃ̂ł���\n���͂ȗ͂��߂Ă���B");
		ItemStatus[9].Itemprice = 9999;
		ItemStatus[9].ItemEffect = 999;
		ItemStatus[9].ItemQuality = EnItemQuality::enLegend;

		for (int num = 0;num < 10 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponSword;
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			ItemStatus[num].ItemType = EnInventoryItemType::Equip;
			//�m�[�}���A�C�e����ID�̓��������X�g�쐬
			if (ItemStatus[num].ItemQuality == EnItemQuality::enNormal)
			{
				m_normalEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			//���A�A�C�e����ID�̓��������X�g�쐬
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enRare)
			{
				m_rareEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			else
			{

			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		
		}
	}

	//����̏�����
	{
		swprintf(ItemStatus[10].ItemName, L"�O���[�g�\�[�h");
		ItemStatus[10].Itemprice = 800;
		ItemStatus[10].ItemEffect = 70;
		ItemStatus[10].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[11].ItemName, L"�o�X�^�[�\�[�h");
		ItemStatus[11].Itemprice = 1200;
		ItemStatus[11].ItemEffect = 150;
		ItemStatus[11].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[12].ItemName, L"�N���C���A");
		ItemStatus[12].Itemprice = 860;
		ItemStatus[12].ItemEffect = 120;
		ItemStatus[12].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[13].ItemName, L"�c���@�C�n���_�[");
		ItemStatus[13].Itemprice = 650;
		ItemStatus[13].ItemEffect = 100;
		ItemStatus[13].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[14].ItemName, L"�R�m�̑匕");
		ItemStatus[14].Itemprice = 700;
		ItemStatus[14].ItemEffect = 130;
		ItemStatus[14].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[15].ItemName, L"���̑匕");
		ItemStatus[15].Itemprice = 3500;
		ItemStatus[15].ItemEffect = 450;
		ItemStatus[15].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[16].ItemName, L"�X�̑匕");
		ItemStatus[16].Itemprice = 3500;
		ItemStatus[16].ItemEffect = 450;
		ItemStatus[16].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[17].ItemName, L"���̑匕");
		ItemStatus[17].Itemprice = 3500;
		ItemStatus[17].ItemEffect = 450;
		ItemStatus[17].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[18].ItemName, L"�ۑ�");
		ItemStatus[18].Itemprice = 10;
		ItemStatus[18].ItemEffect = 20;
		ItemStatus[18].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[19].ItemName, L"�p�Y�̑匕");
		ItemStatus[19].Itemprice = 9999;
		ItemStatus[19].ItemEffect = 999;
		ItemStatus[19].ItemQuality = EnItemQuality::enLegend;
		for (int num = 10;num < 20 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponLongSword;
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			ItemStatus[num].ItemType = EnInventoryItemType::Equip;
			//�m�[�}���A�C�e����ID�̓��������X�g�쐬
			if (ItemStatus[num].ItemQuality == EnItemQuality::enNormal)
			{
				m_normalEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			//���A�A�C�e����ID�̓��������X�g�쐬
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enRare)
			{
				m_rareEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			else
			{

			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}

	return true;
}

void CEquipItem::Update()
{

}
