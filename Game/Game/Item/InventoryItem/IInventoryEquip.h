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
	//itemName			�A�C�e���̖��O
	//textureFilePath	�e�N�X�`���̃t�@�C���p�X
	virtual void Init(const wchar_t* itemName, const wchar_t* textureFilePath) {};

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

	//�e�N�X�`���̃t�@�C���p�X���擾
	const wchar_t* GetTextureFilePath() const
	{
		return m_textureFilePath;
	}

	//�����̃X�e�[�^�X��ݒ�
	//equipStatus	�����X�e�[�^�X
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
	const wchar_t*			m_textureFilePath;		//�e�N�X�`���̃t�@�C���p�X
	SWeaponStatus			m_equipStatus;			//�����̃X�e�[�^�X
};