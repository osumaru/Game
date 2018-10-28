#include "stdafx.h"
#include "PlayerStateMachine.h"


void CPlayerStateMachine::Init()
{
	ChangeState(CPlayerState::enPlayerStand);
}


void CPlayerStateMachine::ChangeState(CPlayerState::EnPlayerState nextState)
{
	if (m_state == nextState) {
		//同じステートなら返す
		return;
	}

	m_state = nextState;

	switch (m_state) {
	case CPlayerState::enPlayerStand:
		m_currentState = &m_playerStand;	//待機アニメーションに遷移
		break;
	case CPlayerState::enPlayerWalk:
		m_currentState = &m_playerWalk;		//歩行アニメーションに遷移
		break;
	case CPlayerState::enPlayerRun:
		m_currentState = &m_playerRun;		//走りアニメーションに遷移
		break;
	case CPlayerState::enPlayerAvoidance:
		m_currentState = &m_playerAvoidance;//回避アニメーションに遷移
		break;
	case CPlayerState::enPlayerJump:
		m_currentState = &m_playerJump;		//ジャンプアニメーションに遷移	
		break;
	case CPlayerState::enPlayerRunJump:
		m_currentState = &m_playerJump;		//走りジャンプアニメーションに遷移	
		break;
	case CPlayerState::enPlayerAttack:
		m_currentState = &m_playerAttack;	//攻撃アニメーションに遷移
		break;
	case CPlayerState::enPlayerArrowAttack:	//弓の攻撃アニメーションに遷移
		m_currentState = &m_playerArrowAtack;
		break;
	case CPlayerState::enPlayerArrowShoot:	//弓の攻撃アニメーションに遷移
		m_currentState = &m_playerArrowShoot;
		break;
	case CPlayerState::enPlayerDamage:
		m_currentState = &m_playerDamege;	//ダメージアニメーションに遷移
		break;
	case CPlayerState::enPlayerDied:
		m_currentState = &m_playerDied;		//死亡アニメーションに遷移
		break;
	case CPlayerState::enPlayerWireMove:
		m_currentState = &m_playerWireMove;	//ワイヤーアニメーションに遷移
	}

	m_currentState->Init();
}

void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}