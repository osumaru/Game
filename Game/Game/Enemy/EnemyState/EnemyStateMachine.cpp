#include "stdafx.h"
#include "EnemyStateMachine.h"

bool CEnemyStateMachine::Start()
{
	if (m_enemyGroup == nullptr) {
		//グループが作られていなければ返す
		return false;
	}
	else {
		//状態クラスにグループを設定
		m_enemyIdle.SetEnemyGroup(m_enemyGroup);
		m_enemyWalk.SetEnemyGroup(m_enemyGroup);
		m_enemyChase.SetEnemyGroup(m_enemyGroup);
		m_enemyAttack.SetEnemyGroup(m_enemyGroup);
		m_enemyDamage.SetEnemyGroup(m_enemyGroup);
		m_enemyDeath.SetEnemyGroup(m_enemyGroup);
	}

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
		m_currentState->Release();
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
	m_currentState->Release();
	Delete(m_currentState);
	Delete(this);
}
