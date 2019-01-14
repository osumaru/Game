#include "stdafx.h"
#include "EnemyStateMachine.h"
#include "../IEnemy.h"

bool CEnemyStateMachine::Start()
{
	if (m_enemyGroup == nullptr) {
		//�O���[�v������Ă��Ȃ���ΕԂ�
		return false;
	}
	else {
		//��ԃN���X�ɃO���[�v��ݒ�
		m_enemyIdle.SetEnemyGroup(m_enemyGroup);
		m_enemyWalk.SetEnemyGroup(m_enemyGroup);
		m_enemyChase.SetEnemyGroup(m_enemyGroup);
		m_enemyAttack.SetEnemyGroup(m_enemyGroup);
		m_enemyDamage.SetEnemyGroup(m_enemyGroup);
		m_enemyStan.SetEnemyGroup(m_enemyGroup);
		m_enemyDeath.SetEnemyGroup(m_enemyGroup);
		m_enemyAttackWait.SetEnemyGroup(m_enemyGroup);
	}

	ChangeState(CEnemyState::enState_Idle);
	return true;
}

void CEnemyStateMachine::Update()
{
	if (m_enemyDeath.GetIsAnimationEnd())
	{
		Release();
	}
}

void CEnemyStateMachine::ChangeState(CEnemyState::EnState nextState)
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
	case CEnemyState::enState_Idle:
		m_currentState = &m_enemyIdle;
		break;
	case CEnemyState::enState_Walk:
		m_currentState = &m_enemyWalk;
		break;
	case CEnemyState::enState_Chase:
		m_currentState = &m_enemyChase;
		break;
	case CEnemyState::enState_Attack:
		m_currentState = &m_enemyAttack;
		break;
	case CEnemyState::enState_Damage:
		m_currentState = &m_enemyDamage;
		break;
	case CEnemyState::enState_Stan:
		m_currentState = &m_enemyStan;
		break;
	case CEnemyState::enState_Death:
		m_currentState = &m_enemyDeath;
		break;
	case CEnemyState::enState_AttackWait:
		m_currentState = &m_enemyAttackWait;
		break;
	}

	//�ύX�����X�e�[�g���Q�[���I�u�W�F�N�g�ɒǉ�
	Add(m_currentState, 0);
}

void CEnemyStateMachine::Release()
{
	Delete(m_currentState);
	Delete(this);
}
