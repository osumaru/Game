/*
*	���N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CSamurai : public IEnemy
{
public:
	//�R���X�g���N�^
	CSamurai();

	//�f�X�g���N�^
	~CSamurai();

	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update();

	//�`��
	void Draw();
};