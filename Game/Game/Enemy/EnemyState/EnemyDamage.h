/*
*	�G�l�~�[�̃_���[�W�N���X
*/

#pragma once

#include "IEnemyState.h"

class CEnemyDamage : public IEnemyState
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyDamage(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyDamage() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

private:

};