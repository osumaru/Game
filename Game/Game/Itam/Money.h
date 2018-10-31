/*
*	�����̃A�C�e���N���X
*/

#pragma once

#include "IItem.h"

class CMoney : public IItem
{
public:
	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�|�b�v������
	void Pop();

	//�����̒l��ݒ�
	//gold		����
	void SetGold(const int gold)
	{
		m_gold = gold;
	}

private:
	int m_gold = 0;	//�����̒l
};