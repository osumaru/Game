/*
*	�����̃A�C�e���N���X
*/

#pragma once

#include "IItem.h"

class CMoney : public IItem
{
public:
	//������
	//gold	�����̒l
	void Init(const int gold);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�|�b�v������
	//position	���W
	void Pop(CVector3 position);

private:
	int m_gold = 0;	//�����̒l
};