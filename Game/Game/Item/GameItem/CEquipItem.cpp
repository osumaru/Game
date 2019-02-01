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
		swprintf(ItemStatus[0].ItemText,L"�q�m�L�ō��ꂽ�،�\n�q���������D��Ŏg���Ă���");
		ItemStatus[0].Itemprice = 10;
		ItemStatus[0].ItemEffect = 10;
		ItemStatus[0].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[1].ItemName, L"���̌�");
		swprintf(ItemStatus[1].ItemText, L"���ō��ꂽ��\n��g�p�Ƃ��Ďg���Ă���");
		ItemStatus[1].Itemprice = 100;
		ItemStatus[1].ItemEffect = 20;
		ItemStatus[1].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[2].ItemName, L"�S�̌�");
		swprintf(ItemStatus[2].ItemText, L"�S�ō��ꂽ��\n���m�����p���Ă�");
		ItemStatus[2].Itemprice = 250;
		ItemStatus[2].ItemEffect = 25;
		ItemStatus[2].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[3].ItemName, L"�|�̌�");
		swprintf(ItemStatus[3].ItemText, L"�|�ō��ꂽ��\n�R�m�����p���Ă���");
		ItemStatus[3].Itemprice = 460;
		ItemStatus[3].ItemEffect = 45;
		ItemStatus[3].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[4].ItemName, L"���@�̌�");
		swprintf(ItemStatus[4].ItemText, L"���͂����߂�ꂽ��\n�㗬�K���݂̂��������Ă���");
		ItemStatus[4].Itemprice = 3000;
		ItemStatus[4].ItemEffect = 70;
		ItemStatus[4].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[5].ItemName, L"�����O�\�[�h");
		swprintf(ItemStatus[5].ItemText, L"�ʏ�̕Ў茕��蒷����\n�n��œG�𓢂��߂�\n���ꂽ");
		ItemStatus[5].Itemprice = 1200;
		ItemStatus[5].ItemEffect = 55;
		ItemStatus[5].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[6].ItemName, L"�o�C�L���O�\�[�h");
		swprintf(ItemStatus[6].ItemText, L"���閯�����g�p���Ă�����");
		ItemStatus[6].Itemprice = 1500;
		ItemStatus[6].ItemEffect = 58;
		ItemStatus[6].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[7].ItemName, L"�Âт���");
		swprintf(ItemStatus[7].ItemText, L"���ѕt������\n���Ȃ�̔N�����o���Ă���\n����Ƃ��Ă͈Ӗ����Ȃ��Ȃ�");
		ItemStatus[7].Itemprice = 1000;
		ItemStatus[7].ItemEffect = 5;
		ItemStatus[7].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[8].ItemName, L"�V���[�g�\�[�h");
		swprintf(ItemStatus[8].ItemText, L"��ʓI�ȕЎ茕\n���������p���Ă���");
		ItemStatus[8].Itemprice = 200;
		ItemStatus[8].ItemEffect = 22;
		ItemStatus[8].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[9].ItemName, L"�p�Y�̌�");
		swprintf(ItemStatus[9].ItemText, L"���̉p�Y�݂̂ɑ����錕\n��U��œG��j�鋭�͂�\n�͂��߂Ă���");
		ItemStatus[9].Itemprice = 99999;
		ItemStatus[9].ItemEffect = 120;
		ItemStatus[9].ItemQuality = EnItemQuality::enSpecial;

		for (int num = 0;num < 10;num++)
		{
			//ID����U��
			ItemStatus[num].ItemID = num + 1;
			//����̎�ނ̐ݒ�
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponSword;
			//�C���x���g���ɕ\������X�v���C�g�̏��
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/sword.png");
			//�e�����y�ڂ��X�e�[�^�X
			ItemStatus[num].ItemEffectPlayerStatus = EnIemEffectPlayerStatus::Strength;
			//�����̃^�C�v�̐ݒ�
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		
		}
	}

	//����̏�����
	{
		swprintf(ItemStatus[10].ItemName, L"�O���[�g�\�[�h");
		swprintf(ItemStatus[10].ItemText, L"����ȑ匕\n�͂ɔC�����͂̕��𕲍ӂ���\n���낵���͂��߂Ă���B");
		ItemStatus[10].Itemprice = 100;
		ItemStatus[10].ItemEffect = 25;
		ItemStatus[10].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[11].ItemName, L"�o�X�^�[�\�[�h");
		swprintf(ItemStatus[11].ItemText, L"�o�X�^�[�\�[�h�B�O���[\n�g�\�[�h�Ɠ������A�G��\n���ӂ��邽�߂ɍ�\n��ꂽ���͂ȑ匕�B");
		ItemStatus[11].Itemprice = 380;
		ItemStatus[11].ItemEffect = 30;
		ItemStatus[11].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[12].ItemName, L"�N���C���A");
		swprintf(ItemStatus[12].ItemText, L"�N���C���A�B�d�����ꌂ\n������𕲍ӂ���匕�B");
		ItemStatus[12].Itemprice = 2600;
		ItemStatus[12].ItemEffect = 60;
		ItemStatus[12].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[13].ItemName, L"�c���@�C�n���_�[");
		swprintf(ItemStatus[13].ItemText, L"�c���@�C�n���_�[�B�U��\n�񂷂��Ƃɂ��A��苭\n�͂Ȉꌂ����B");
		ItemStatus[13].Itemprice = 2700;
		ItemStatus[13].ItemEffect = 63;
		ItemStatus[13].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[14].ItemName, L"�R�m�̑匕");
		swprintf(ItemStatus[14].ItemText, L"�R�m�̑匕�B�������≤\n�̑��߂̕����g�ɒ�����\n����B");
		ItemStatus[14].Itemprice = 4000;
		ItemStatus[14].ItemEffect = 80;
		ItemStatus[14].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[15].ItemName, L"���̑匕");
		swprintf(ItemStatus[15].ItemText, L"���̑匕�B���̖��͂���\n�߂�ꂽ�匕�B");
		ItemStatus[15].Itemprice = 7000;
		ItemStatus[15].ItemEffect = 100;
		ItemStatus[15].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[16].ItemName, L"�X�̑匕");
		swprintf(ItemStatus[16].ItemText, L"�X�̑匕�B�X�̖��͂���\n�߂�ꂽ�匕�B");
		ItemStatus[16].Itemprice = 7000;
		ItemStatus[16].ItemEffect = 100;
		ItemStatus[16].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[17].ItemName, L"���̑匕");
		swprintf(ItemStatus[17].ItemText, L"���̑匕�B���̖��͂���\n�߂�ꂽ�匕�B");
		ItemStatus[17].Itemprice = 7000;
		ItemStatus[17].ItemEffect = 100;
		ItemStatus[17].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[18].ItemName, L"�ۑ�");
		swprintf(ItemStatus[18].ItemText, L"�ۑ��B����̂Ƃ��Ă̎�\n�p���͂Ȃ����A�����U\n��񂷋ؗ͂͌v��m��Ȃ��B");
		ItemStatus[18].Itemprice = 10;
		ItemStatus[18].ItemEffect = 10;
		ItemStatus[18].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[19].ItemName, L"�p�Y�̑匕");
		swprintf(ItemStatus[19].ItemText, L"���̉p�Y�݂̂ɑ�����\n�匕�B��U��Ŏ��͂̓G\n�𕲍ӂ��鋭�͂ȗ͂��߂Ă���B");
		ItemStatus[19].Itemprice = 99999;
		ItemStatus[19].ItemEffect = 150;
		ItemStatus[19].ItemQuality = EnItemQuality::enSpecial;
		for (int num = 10;num < 20;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponLongSword;
			//�C���x���g���ɕ\������X�v���C�g�̏��
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/largeSword.png");
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
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
		ItemStatus[21].Itemprice = 50;
		ItemStatus[21].ItemEffect = 7;
		ItemStatus[21].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[22].ItemName, L"���m�̋|");
		swprintf(ItemStatus[22].ItemText, L"���m�̋|�B��ɕ��m���푈����\n�G��j�邽�߂Ɏg����\n����B");
		ItemStatus[22].Itemprice = 240;
		ItemStatus[22].ItemEffect = 15;
		ItemStatus[22].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[23].ItemName, L"�X�l�̋|");
		swprintf(ItemStatus[23].ItemText, L"�X�l�̋|�B�X�l�����Ɏg���|�B\n����ȗ͂����߂��Ă�\n��B");
		ItemStatus[23].Itemprice = 600;
		ItemStatus[23].ItemEffect = 25;
		ItemStatus[23].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[24].ItemName, L"�{���C�|");
		swprintf(ItemStatus[24].ItemText, L"�{���C�|�B�|���΂����Ƃ��ł���\n���A���قǈЗ͂͂Ȃ��B");
		ItemStatus[24].Itemprice = 0;
		ItemStatus[24].ItemEffect = 1;
		ItemStatus[24].ItemQuality = EnItemQuality::enNormal;
		swprintf(ItemStatus[25].ItemName, L"�����O�{�E");
		swprintf(ItemStatus[25].ItemText, L"�����O�{�E�B�ʏ�̋|���傫���A��\n�̋|����������ꌂ\n���d�����B");
		ItemStatus[25].Itemprice = 1200;
		ItemStatus[25].ItemEffect = 40;
		ItemStatus[25].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[26].ItemName, L"���l�̋|");
		swprintf(ItemStatus[26].ItemText, L"���l�̋|�B�Â̎���ɂ������l�����g�p\n���Ă����|�B");
		ItemStatus[26].Itemprice = 2500;
		ItemStatus[26].ItemEffect = 50;
		ItemStatus[26].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[27].ItemName, L"�Ñ�̋|");
		swprintf(ItemStatus[27].ItemText, L"�Ñ�̋|�B�Â̎���̋Z�p�ɂ���č���\n�����͂ȋ|�B");
		ItemStatus[27].Itemprice = 4500;
		ItemStatus[27].ItemEffect = 65;
		ItemStatus[27].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[28].ItemName, L"���҂̋|");
		swprintf(ItemStatus[28].ItemText, L"���҂̋|�B����A���҂��g�p���Ă����|�B��\n�͂Ȗ��͂����߂�\n��Ă���B�B");
		ItemStatus[28].Itemprice = 8000;
		ItemStatus[28].ItemEffect = 76;
		ItemStatus[28].ItemQuality = EnItemQuality::enLegend;
		swprintf(ItemStatus[29].ItemName, L"�p�Y�̋|");
		swprintf(ItemStatus[29].ItemText, L"���̉p�Y�݂̂ɑ�����|�B�G���ꌂ�œj�鋭\n�͂Ȗ����B");
		ItemStatus[29].Itemprice = 99999;
		ItemStatus[29].ItemEffect = 90;
		ItemStatus[29].ItemQuality = EnItemQuality::enSpecial;
		for (int num = 20;num < 30;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponArrow;
			//�C���x���g���ɕ\������X�v���C�g�̏��
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/bow.png");
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}
	//�|�̏�����
	{
		swprintf(ItemStatus[30].ItemName, L"�؂̑o��");
		swprintf(ItemStatus[30].ItemText, L"�؂łł����o���B\n�삯�o���̖`���҂��g�p���Ă���B");
		ItemStatus[30].Itemprice = 10;
		ItemStatus[30].ItemEffect = 4;
		ItemStatus[30].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[31].ItemName, L"�o�^�t���C�\�[�h");
		swprintf(ItemStatus[31].ItemText, L"���l�̋|�B��ɗ�������҂�\n�����H�����m�ۂ��邽��\n�Ɏg�p���Ă���B");
		ItemStatus[31].Itemprice = 120;
		ItemStatus[31].ItemEffect = 10;
		ItemStatus[31].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[32].ItemName, L"���m�̑o��");
		swprintf(ItemStatus[32].ItemText, L"���m�̋|�B��ɕ��m���푈����\n�G��j�邽�߂Ɏg����\n����B");
		ItemStatus[32].Itemprice = 340;
		ItemStatus[32].ItemEffect = 14;
		ItemStatus[32].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[33].ItemName, L"�O���f�B�E�X");
		swprintf(ItemStatus[33].ItemText, L"�X�l�̋|�B�X�l�����Ɏg���|�B\n����ȗ͂����߂��Ă�\n��B");
		ItemStatus[33].Itemprice = 3500;
		ItemStatus[33].ItemEffect = 40;
		ItemStatus[33].ItemQuality = EnItemQuality::enRare;

		swprintf(ItemStatus[34].ItemName, L"�����̃_�K�[");
		swprintf(ItemStatus[34].ItemText, L"�{���C�|�B�|���΂����Ƃ��ł���\n���A���قǈЗ͂͂Ȃ��B");
		ItemStatus[34].Itemprice = 500;
		ItemStatus[34].ItemEffect = 20;
		ItemStatus[34].ItemQuality = EnItemQuality::enNormal;

		swprintf(ItemStatus[35].ItemName, L"�t�@���V�I��");
		swprintf(ItemStatus[35].ItemText, L"�����O�{�E�B�ʏ�̋|���傫���A��\n�̋|����������ꌂ\n���d�����B");
		ItemStatus[35].Itemprice = 2400;
		ItemStatus[35].ItemEffect = 30;
		ItemStatus[35].ItemQuality = EnItemQuality::enLegend;

		swprintf(ItemStatus[36].ItemName, L"�V���[�e��");
		swprintf(ItemStatus[36].ItemText, L"���l�̋|�B�Â̎���ɂ������l�����g�p\n���Ă����|�B");
		ItemStatus[36].Itemprice = 1500;
		ItemStatus[36].ItemEffect = 25;
		ItemStatus[36].ItemQuality = EnItemQuality::enRare;

		swprintf(ItemStatus[37].ItemName, L"�c�C���\�[�h");
		swprintf(ItemStatus[37].ItemText, L"�Ñ�̋|�B�Â̎���̋Z�p�ɂ���č���\n�����͂ȋ|�B");
		ItemStatus[37].Itemprice = 1200;
		ItemStatus[37].ItemEffect = 23;
		ItemStatus[37].ItemQuality = EnItemQuality::enRare;
		swprintf(ItemStatus[38].ItemName, L"���t�B�X�g�t�F���X");
		swprintf(ItemStatus[38].ItemText, L"���҂̋|�B����A���҂��g�p���Ă����|�B��\n�͂Ȗ��͂����߂�\n��Ă���B�B");
		ItemStatus[38].Itemprice = 4500;
		ItemStatus[38].ItemEffect = 46;
		ItemStatus[38].ItemQuality = EnItemQuality::enLegend;

		swprintf(ItemStatus[39].ItemName, L"�p�Y�̑o��");
		swprintf(ItemStatus[39].ItemText, L"���̉p�Y�݂̂ɑ�����o���B\n�B");
		ItemStatus[39].Itemprice = 99999;
		ItemStatus[39].ItemEffect = 60;
		ItemStatus[39].ItemQuality = EnItemQuality::enSpecial;

		for (int num = 30;num < 40;num++)
		{
			ItemStatus[num].ItemID = num + 1;
			ItemStatus[num].WeaponType = EnPlayerWeapon::enWeaponTwinSword;
			//�C���x���g���ɕ\������X�v���C�g�̏��
			swprintf(ItemStatus[num].ItemSprite, L"Assets/sprite/twinSword.png");
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
			else if (ItemStatus[num].ItemQuality == EnItemQuality::enLegend)
			{
				m_legendEquipItemList.push_back(ItemStatus[num].ItemID);
			}
			m_equipItemStatusList.push_back(ItemStatus[num]);
		}
	}
	//�f�[�^�̎擾����
	/*std::fstream file;
	file.open("Assets/ItemList/Equip.dta", std::ios::binary | std::ios::out | std::ios::trunc);
	file.write((char*)ItemStatus, sizeof(ItemStatus));
	file.close();
	file.open("Assets/ItemList/Equip.dta", std::ios::binary | std::ios::in);
	for (auto& list : ItemStatus)
	{
		file.read((char*)&list, sizeof(SItemStatus));
	}
	file.close();*/
	return true;
}

void CEquipItem::Update()
{

}
