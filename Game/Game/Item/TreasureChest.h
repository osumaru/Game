/*
*	�����A�C�e���N���X
*/

#pragma once

#include "IItem.h"
#include "InventoryItem/IInventoryEquip.h"
#include"GameItem/CEquipItem.h"

class CTreasureChest : public IItem
{
public:
	//������
	//position		���W
	//isMapItem		�}�b�v�ɔz�u���邩
	void Init(CVector3 position, CQuaternion rotation, bool isMapItem);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//����̃X�e�[�^�X�����߂�
	void DesideWeaponStatus();

	//���ɂ��镐��̃N�I���e�B��ݒ肷��
	//weaponQuality		���ɂ��镐��̃N�I���e�B
	void SetWeaponQuality(EnItemQuality weaponQuality)
	{
		m_weaponQuality = weaponQuality;
	}

private:
	std::unique_ptr<IInventoryEquip> m_inventoryEquip;	//�C���x���g���ɓ���鑕��
	EnItemQuality m_weaponQuality = enUnknown;	//���ɂ��镐��̃N�I���e�B
	CLight	m_light;				//���C�g
	bool m_itemDrawCount = false;	//�A�C�e�����E��UI���o���J�E���g�����łɂ��Ă��邩
	bool m_isMapItem = false;		//�}�b�v�ɔz�u���邩
};