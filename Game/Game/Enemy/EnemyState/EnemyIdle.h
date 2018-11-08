/*
*	�G�l�~�[�̑ҋ@�N���X
*/

#pragma once

#include "IEnemyState.h"

class CEnemyIdle : public IEnemyState 
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	//esm		�G�l�~�[�̃X�e�[�g�}�V���N���X�̃|�C���^
	CEnemyIdle(IEnemy* enemy, CEnemyStateMachine* esm):
		IEnemyState(enemy, esm)
	{
	}

	//�f�X�g���N�^
	~CEnemyIdle() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

private:
	float m_timer = 0.0f;	//�^�C�}�[
};