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
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�ړ�
	void Move();
};