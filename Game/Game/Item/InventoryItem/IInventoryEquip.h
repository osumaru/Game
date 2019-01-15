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
	virtual void Init(const wchar_t* itemName, const wchar_t* textureFileName) {};

	//�`��
	virtual void Draw() {};

	//�A�C�e���̃X�v���C�g���擾
	CSprite* GetSprite()
	{
		return &m_itemSprite;
	}

	//�A�C�e���̖��O���擾
	const wchar_t* GetItemName() const
	{
		return m_itemName;
	}

	//�e�N�X�`���t�@�C���̖��O���擾
	const wchar_t* GetTextureFileName() const
	{
		return m_textureFileName;
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
	const wchar_t*			m_itemName;				//�A�C�e���̖��O
	const wchar_t*			m_textureFileName;		//�e�N�X�`���t�@�C���̖��O
	SWeaponStatus			m_equipStatus;			//�����̃X�e�[�^�X
};