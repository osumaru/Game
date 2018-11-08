/*
*	�G�l�~�[�̕����N���X
*/

#pragma once

#include "IEnemyState.h"

class CEnemyWalk : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyWalk(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyWalk() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;
};