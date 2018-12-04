/*
*	�C���x���g���ɓ����A�C�e���̃C���^�[�t�F�[�X�N���X
*/

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

protected:
	CSprite					m_itemSprite;			//�A�C�e���̃X�v���C�g
	wchar_t*				m_itemName;				//�A�C�e���̖��O
};