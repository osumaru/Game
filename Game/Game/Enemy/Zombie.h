/*
*	�]���r�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CZombie : public IEnemy
{
public:
	//�R���X�g���N�^
	CZombie();

	//�f�X�g���N�^
	~CZombie();

	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update();

	//�`��
	void Draw();
};