/*
*	�C���x���g���ɓ����A�C�e���̃C���^�[�t�F�[�X�N���X
*/
#include "../GameItem/ItemStatus.h"
#pragma once

class IInventoryItem
{
public:
	//�R���X�g���N�^
	IInventoryItem() {};

	//�f�X�g���N�^
	virtual ~IInventoryItem() {};

	//������
	virtual void Init() {};

	//�`��
	virtual void Draw() {};

	//�A�C�e�����g��
	virtual bool Use() { return false; }

	virtual void TexUpdate() {};

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

	//�X�e�[�^�X��ݒ�
	void SetStatus(const SItemStatus& status)
	{
		m_status = status;
	}

	//�X�e�[�^�X���擾
	const SItemStatus& GetStatus() const
	{
		return m_status;
	}

protected:
	SItemStatus				m_status;				//�A�C�e���̃X�e�[�^�X
	CSprite					m_itemSprite;			//�A�C�e���̃X�v���C�g
	wchar_t*				m_itemName;				//�A�C�e���̖��O
};