/*
*	�G�l�~�[�̎��S�N���X
*/

#pragma once

#include "IEnemyState.h"

class EnemyDeath : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	EnemyDeath(IEnemy* enemy, EnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~EnemyDeath() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

private:

};