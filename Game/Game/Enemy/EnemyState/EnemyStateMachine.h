/*
*	�G�l�~�[�̃X�e�[�g�}�V��
*/

#pragma once

#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDeath.h"
#include "IEnemyState.h"
#include "EnemyState.h"

class EnemyStateMachine : public IGameObject
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	EnemyStateMachine(IEnemy* enemy) :
		m_enemyIdle(enemy, this),
		m_enemyWalk(enemy, this),
		m_enemyAttack(enemy, this),
		m_enemyDamage(enemy, this),
		m_enemyDeath(enemy, this)
	{
	}

	//�f�X�g���N�^
	~EnemyStateMachine() {}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update() 
	{
	}

	//�X�e�[�g�̐؂�ւ�
	void ChangeState(EnemyState::EnState nextState);

	//���
	void Release();

private:
	EnemyState::EnState m_state = EnemyState::enState_Invald;	//�G�l�~�[�̏��
	IEnemyState*		m_currentState = nullptr;				//���݂̏��
	EnemyIdle			m_enemyIdle;							//�ҋ@
	EnemyWalk			m_enemyWalk;							//����
	EnemyAttack			m_enemyAttack;							//�U��
	EnemyDamage			m_enemyDamage;							//�_���[�W
	EnemyDeath			m_enemyDeath;							//���S
};