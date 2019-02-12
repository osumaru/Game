#pragma once
#pragma once
#include "InventoryItem/IInventoryItem.h"
//�v���C���[�̏������Ă���A�C�e���̃��X�g

class CItemList
{
public:
	//�A�C�e�����̂Ă�
	//pointerNum	�����A�C�e���̈ʒu
	void Erase(int pointerNum);

	void Use(int pointerNum);

	//�����A�C�e�����X�g�ɒǉ�
	//item		�A�C�e�����X�g�ɒǉ�����A�C�e��
	void AddItemList(std::unique_ptr<IInventoryItem> item);

	//�A�C�e�����X�g���擾
	std::list<std::unique_ptr<IInventoryItem>>& GetBody()
	{
		return m_itemList;
	}

	//�X�v���C�g�̍��W��ݒ�
	void SetSpritePos(int idx, const CVector2& pos);

	//�X�v���C�g�̃T�C�Y���擾
	void SetSpriteSize(int idx, const CVector2& size);

	//�`��
	void Draw();

	//�A�C�e�����X�g�ɃX�y�[�X���󂢂Ă邩�̃t���O���擾
	bool IsSpaceItemList();

	//�A�C�e�����擾
	//pointerNum 
	IInventoryItem* GetItem(int pointerNum);

	static const int	m_itemLimit = 25;			//�A�C�e���������
private:
	std::list<std::unique_ptr<IInventoryItem>>	m_itemList;	//�A�C�e�����X�g
};
