/*
*	�]���r�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class Zombie : public IEnemy
{
public:
	//�R���X�g���N�^
	Zombie();

	//�f�X�g���N�^
	~Zombie();

	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update();

	//�`��
	void Draw();
};