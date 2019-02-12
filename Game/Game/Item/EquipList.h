#pragma once
#include "InventoryItem/IInventoryEquip.h"

class CEquipList
{
public:
	//�A�C�e�����̂Ă�
//pointerNum	�����A�C�e���̈ʒu
	void Erase(int pointerNum);

	//�����A�C�e�����X�g�ɒǉ�
	//item		�A�C�e�����X�g�ɒǉ�����A�C�e��
	void AddEquipList(std::unique_ptr<IInventoryEquip> item);

	//�A�C�e�����X�g���擾
	std::list<std::unique_ptr<IInventoryEquip>>& GetBody()
	{
		return m_equipList;
	}

	//�X�v���C�g�̍��W��ݒ�
	void SetSpritePos(int idx, const CVector2& pos);

	//�X�v���C�g�̃T�C�Y���擾
	void SetSpriteSize(int idx, const CVector2& size);

	//�`��
	void Draw();

	//�A�C�e�����X�g�ɃX�y�[�X���󂢂Ă邩�̃t���O���擾
	bool IsSpaceEquipList();

	//�A�C�e�����擾
	//pointerNum 
	IInventoryEquip* GetEquip(int pointerNum);

	static const int m_equipLimit = 15;								//�����������
private:
	std::list<std::unique_ptr<IInventoryEquip>>	m_equipList;//�������X�g
};