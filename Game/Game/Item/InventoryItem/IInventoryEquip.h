#pragma once

class IIventoryEquip 
{
	//�R���X�g���N�^
	IIventoryEquip() {};

	//�f�X�g���N�^
	virtual ~IIventoryEquip() {};

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

protected:
	CSprite					m_itemSprite;			//�A�C�e���̃X�v���C�g
	wchar_t*				m_itemName;				//�A�C�e���̖��O
};