#include "stdafx.h"
#include "EnemyStateMachine.h"

bool CEnemyStateMachine::Start()
{
	ChangeState(CEnemyState::enState_Idle);
	return true;
}

void CEnemyStateMachine::ChangeState(CEnemyState::EnState nextState)
{
	if (m_state == nextState) {
		//同じステートなら返す
		return;
	}

	//現在のステートをゲームオブジェクトから削除
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
	case CEnemyState::enState_Death:
		m_currentState = &m_enemyDeath;
		break;
	}

	//変更したステートをゲームオブジェクトに追加
	Add(m_currentState, 0);
}

void CEnemyStateMachine::Release()
{
	Delete(m_currentState);
	Delete(this);
}
