/*
*	�G�̃C���^�[�t�F�[�X�N���X
*/

#pragma once

#include "EnemyStateMachine.h"

class IEnemy : public IGameObject
{
public:
	//�R���X�g���N�^
	IEnemy();

	//�f�X�g���N�^
	~IEnemy();

	//������
	virtual void Init(CVector3 position) = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;
};