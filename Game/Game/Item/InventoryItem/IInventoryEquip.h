#pragma once

#include "../../Player/Weapon/WeaponCommon.h"

class IInventoryEquip 
{
public:
	//�R���X�g���N�^
	IInventoryEquip() {};

	//�f�X�g���N�^
	virtual ~IInventoryEquip() {};

	//������
	virtual void Init() {};

	//�`��
	virtual void Draw() {};

	//�A�C�e���̃X�v���C�g���擾
	CSprite* GetSprite()
	{
		return &m_itemSprite;
	}

	//�A�C�e���̖��O���擾
	wchar_t* GetItemName()
	{
		return m_itemName;
	}

	//�����̃X�e�[�^�X��ݒ�
	void SetEquipStatus(SWeaponStatus equipStatus)
	{
		m_equipStatus = equipStatus;
	}

	//�����̃X�e�[�^�X���擾
	SWeaponStatus GetEquipStatus()
	{
		return m_equipStatus;
	}

protected:
	CSprite					m_itemSprite;			//�A�C�e���̃X�v���C�g
	wchar_t*				m_itemName;				//�A�C�e���̖��O
	SWeaponStatus			m_equipStatus;			//�����̃X�e�[�^�X
};