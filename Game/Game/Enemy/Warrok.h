/*
*	�E�H�[���b�N�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CWarrok : public IEnemy
{
public:
	//�R���X�g���N�^
	CWarrok();

	//�f�X�g���N�^
	~CWarrok();

	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update();

	//�`��
	void Draw();
};