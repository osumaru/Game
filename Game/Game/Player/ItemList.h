#pragma once
#include "../Item/InventoryItem/IInventoryItem.h"
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

	void SetSpritePos(int idx, const CVector2& pos);

	void SetSpriteSize(int idx, const CVector2& size);

	void Draw();

	bool IsSpaceItemList();

	static const int	m_itemLimit = 25;			//�A�C�e���������
private:
	std::list<std::unique_ptr<IInventoryItem>>	m_itemList;	//�A�C�e�����X�g
};
