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
		swprintf(ItemStatus[0].ItemText,L"�q�m�؂ō��ꂽ�،�.�q��\n�������D��Ŏg���Ă���B");
		ItemStatus[0].Itemprice = 10;
		ItemStatus[0].ItemEffect = 10;
		ItemStatus[0].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[1].ItemName, L"���̌� ");
		swprintf(ItemStatus[1].ItemText, L"	���ō��ꂽ��.��g�p\n�Ƃ��čD��Ŏg���Ă���B");
		ItemStatus[1].Itemprice = 50;
		ItemStatus[1].ItemEffect = 20;
		ItemStatus[1].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[2].ItemName, L"�S�̌� ");
		swprintf(ItemStatus[2].ItemText, L"�S�ō��ꂽ��.���m��\n�b���`���҂����p���Ă�");
		ItemStatus[2].Itemprice = 100;
		ItemStatus[2].ItemEffect = 40;
		ItemStatus[2].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[3].ItemName, L"�|�̌� ");
		swprintf(ItemStatus[3].ItemText, L"�|�ō��ꂽ��.�R�m�╺��\n���ȂǏ�ʐE�̎҂����p\n���Ă���B");
		ItemStatus[3].Itemprice = 250;
		ItemStatus[3].ItemEffect = 60;
		ItemStatus[3].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[4].ItemName, L"���@�̌�");
		swprintf(ItemStatus[4].ItemText, L"���͂����߂�ꂽ��.�ꕔ��\n�㗬�K���݂̂���������\n����B");
		ItemStatus[4].Itemprice = 3500;
		ItemStatus[4].ItemEffect = 350;
		ItemStatus[4].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[5].ItemName, L"�����O�\�[�h ");
		swprintf(ItemStatus[5].ItemText, L"�ʏ�̕Ў茕��蒷����.�n��\n�œG�𓢂��߂ɍ��\n�ꂽ�B");
		ItemStatus[5].Itemprice = 1000;
		ItemStatus[5].ItemEffect = 120;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[6].ItemName, L"�o�C�L���O�\�[�h");
		swprintf(ItemStatus[6].ItemText, L"���閯�����g�p���Ă���������\n�̒��ł��㗬�K���̎҂�\n���p���Ă�������B");
		ItemStatus[6].Itemprice = 1400;
		ItemStatus[6].ItemEffect = 145;
		ItemStatus[6].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[7].ItemName, L"�Âт���");
		swprintf(ItemStatus[7].ItemText, L"���ѕt������.���Ȃ�̔N����\n�o���Ă��蕐��Ƃ��Ă�\n�قƂ�ǈӖ����Ȃ��Ȃ��B");
		ItemStatus[7].Itemprice = 1000;
		ItemStatus[7].ItemEffect = 5;
		ItemStatus[7].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[8].ItemName, L"�V���[�g�\�[�h");
		swprintf(ItemStatus[8].ItemText, L"��ʓI�ȕЎ茕.��ɕ�������\n�p���Ă���B");
		ItemStatus[8].Itemprice = 200;
		ItemStatus[8].ItemEffect = 55;
		ItemStatus[8].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[9].ItemName, L"�p�Y�̌�");
		swprintf(ItemStatus[9].ItemText, L"���̉p�Y�݂̂ɑ����錕.��U\n��œG��j�邱�Ƃ̂ł�\n�鋭�͂ȗ͂��߂Ă���B");
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
		swprintf(ItemStatus[10].ItemText, L"����ȑ匕�B�͂ɔC����\n�͂̕��𕲍ӂ��鋰�낵\n���͂��߂Ă���B");
		ItemStatus[10].Itemprice = 100;
		ItemStatus[10].ItemEffect = 85;
		ItemStatus[10].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[11].ItemName, L"�o�X�^�[�\�[�h");
		swprintf(ItemStatus[11].ItemText, L"�o�X�^�[�\�[�h�B�O���[\n�g�\�[�h�Ɠ������A�G��\n���ӂ��邽�߂ɍ�\n��ꂽ���͂ȑ匕�B");
		ItemStatus[11].Itemprice = 1200;
		ItemStatus[11].ItemEffect = 220;
		ItemStatus[11].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[12].ItemName, L"�N���C���A");
		swprintf(ItemStatus[12].ItemText, L"�N���C���A�B�d�����ꌂ\n������𕲍ӂ���匕�B");
		ItemStatus[12].Itemprice = 860;
		ItemStatus[12].ItemEffect = 185;
		ItemStatus[12].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[13].ItemName, L"�c���@�C�n���_�[");
		swprintf(ItemStatus[13].ItemText, L"�c���@�C�n���_�[�B�U��\n�񂷂��Ƃɂ��A��苭\n�͂Ȉꌂ����B");
		ItemStatus[13].Itemprice = 650;
		ItemStatus[13].ItemEffect = 160;
		ItemStatus[13].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[14].ItemName, L"�R�m�̑匕");
		swprintf(ItemStatus[14].ItemText, L"�R�m�̑匕�B�������≤\n�̑��߂̕����g�ɒ�����\n����B");
		ItemStatus[14].Itemprice = 1000;
		ItemStatus[14].ItemEffect = 210;
		ItemStatus[14].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[15].ItemName, L"���̑匕");
		swprintf(ItemStatus[15].ItemText, L"���̑匕�B���̖��͂���\n�߂�ꂽ�匕�B");
		ItemStatus[15].Itemprice = 3500;
		ItemStatus[15].ItemEffect = 450;
		ItemStatus[15].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[16].ItemName, L"�X�̑匕");
		swprintf(ItemStatus[16].ItemText, L"�X�̑匕�B�X�̖��͂���\n�߂�ꂽ�匕�B");
		ItemStatus[16].Itemprice = 3500;
		ItemStatus[16].ItemEffect = 450;
		ItemStatus[16].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[17].ItemName, L"���̑匕");
		swprintf(ItemStatus[17].ItemText, L"���̑匕�B���̖��͂���\n�߂�ꂽ�匕�B");
		ItemStatus[17].Itemprice = 3500;
		ItemStatus[17].ItemEffect = 450;
		ItemStatus[17].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[18].ItemName, L"�ۑ�");
		swprintf(ItemStatus[18].ItemText, L"�ۑ��B����̂Ƃ��Ă̎�\n�p���͂Ȃ����A�����U\n��񂷋ؗ͂͌v��m��Ȃ��B");
		ItemStatus[18].Itemprice = 10;
		ItemStatus[18].ItemEffect = 30;
		ItemStatus[18].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[19].ItemName, L"�p�Y�̑匕");
		swprintf(ItemStatus[19].ItemText, L"���̉p�Y�݂̂ɑ�����\n�匕�B��U��Ŏ��͂̓G\n�𕲍ӂ��鋭�͂ȗ͂��߂Ă���B");
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

	//�|�̏�����
	{
		swprintf(ItemStatus[20].ItemName, L"�؂̋|");
		swprintf(ItemStatus[20].ItemText, L"�؂łł����|�B�삯�o����\n�`���҂��g�p���邱�Ƃ�\n�����B");
		ItemStatus[20].Itemprice = 10;
		ItemStatus[20].ItemEffect = 5;
		ItemStatus[20].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[21].ItemName, L"���l�̋|");
		swprintf(ItemStatus[21].ItemText, L"���l�̋|�B��ɗ�������҂�\n�����H�����m�ۂ��邽��\n�Ɏg�p���Ă���B");
		ItemStatus[21].Itemprice = 15;
		ItemStatus[21].ItemEffect = 7;
		ItemStatus[21].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[22].ItemName, L"���m�̋|");
		swprintf(ItemStatus[22].ItemText, L"���m�̋|�B��ɕ��m���푈����\n�G��j�邽�߂Ɏg����\n����B");
		ItemStatus[22].Itemprice = 100;
		ItemStatus[22].ItemEffect = 20;
		ItemStatus[22].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[23].ItemName, L"�X�l�̋|");
		swprintf(ItemStatus[23].ItemText, L"�X�l�̋|�B�X�l�����Ɏg���|�B\n����ȗ͂����߂��Ă�\n��B");
		ItemStatus[23].Itemprice = 600;
		ItemStatus[23].ItemEffect = 45;
		ItemStatus[23].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[24].ItemName, L"�{���C�|");
		swprintf(ItemStatus[24].ItemText, L"�{���C�|�B�|���΂����Ƃ��ł���\n���A���قǈЗ͂͂Ȃ��B");
		ItemStatus[24].Itemprice = 0;
		ItemStatus[24].ItemEffect = 1;
		ItemStatus[24].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[25].ItemName, L"�����O�{�E");
		swprintf(ItemStatus[25].ItemText, L"�����O�{�E�B�ʏ�̋|���傫���A��\n�̋|����������ꌂ\n���d�����B");
		ItemStatus[25].Itemprice = 760;
		ItemStatus[25].ItemEffect = 50;
		ItemStatus[25].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[26].ItemName, L"���l�̋|");
		swprintf(ItemStatus[26].ItemText, L"���l�̋|�B�Â̎���ɂ������l�����g�p\n���Ă����|�B");
		ItemStatus[26].Itemprice = 2500;
		ItemStatus[26].ItemEffect = 90;
		ItemStatus[26].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[27].ItemName, L"�Ñ�̋|");
		swprintf(ItemStatus[27].ItemText, L"�Ñ�̋|�B�Â̎���̋Z�p�ɂ���č���\n�����͂ȋ|�B");
		ItemStatus[27].Itemprice = 4500;
		ItemStatus[27].ItemEffect = 120;
		ItemStatus[27].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[28].ItemName, L"���҂̋|");
		swprintf(ItemStatus[28].ItemText, L"���҂̋|�B����A���҂��g�p���Ă����|�B��\n�͂Ȗ��͂����߂�\n��Ă���B�B");
		ItemStatus[28].Itemprice = 8000;
		ItemStatus[28].ItemEffect = 350;
		ItemStatus[28].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[29].ItemName, L"�p�Y�̋|");
		swprintf(ItemStatus[29].ItemText, L"���̉p�Y�݂̂ɑ�����|�B�G���ꌂ�œj�鋭\n�͂Ȗ����B");
		ItemStatus[29].Itemprice = 9999;
		ItemStatus[29].ItemEffect = 999;
		ItemStatus[29].ItemQuality = EnItemQuality::enLegend;
		for (int num = 20;num < 30 /*MAX_ITEM_NUMBER*/;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponArrow;
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
