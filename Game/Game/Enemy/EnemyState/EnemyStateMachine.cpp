#include "stdafx.h"
#include "EnemyStateMachine.h"

bool EnemyStateMachine::Start()
{
	ChangeState(EnemyState::enState_Idle);
	return true;
}

void EnemyStateMachine::ChangeState(EnemyState::EnState nextState)
{
	if (m_state == nextState) {
		//�����X�e�[�g�Ȃ�Ԃ�
		return;
	}

	//���݂̃X�e�[�g���Q�[���I�u�W�F�N�g����폜
	if (m_currentState != nullptr) {
		Delete(m_currentState);
	}

	m_state = nextState;

	switch (m_state) {
	case EnemyState::enState_Idle:
		m_currentState = &m_enemyIdle;
		break;
	case EnemyState::enState_Walk:
		m_currentState = &m_enemyWalk;
		break;
	case EnemyState::enState_Attack:
		m_currentState = &m_enemyAttack;
		break;
	case EnemyState::enState_Damage:
		m_currentState = &m_enemyDamage;
		break;
	case EnemyState::enState_Death:
		m_currentState = &m_enemyDeath;
		break;
	}

	//�ύX�����X�e�[�g���Q�[���I�u�W�F�N�g�ɒǉ�
	Add(m_currentState, 0);
}

void EnemyStateMachine::Release()
{
	Delete(m_currentState);
	Delete(this);
}
