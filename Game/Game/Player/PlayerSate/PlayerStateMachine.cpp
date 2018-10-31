#include "stdafx.h"
#include "PlayerStateMachine.h"


void CPlayerStateMachine::Init()
{
	SetState(CPlayerState::enPlayerStateStand);
}


void CPlayerStateMachine::SetState(CPlayerState::EnPlayerState nextState)
{
	if (m_state == nextState) {
		//同じステートなら返す
		return;
	}

	m_state = nextState;

	switch (m_state) {
	case CPlayerState::enPlayerStateStand:
		m_currentState = &m_playerStand;			//待機アニメーションに遷移
		break;
	case CPlayerState::enPlayerStateWalk:
		m_currentState = &m_playerWalk;				//歩行アニメーションに遷移
		break;
	case CPlayerState::enPlayerStateRun:
		m_currentState = &m_playerRun;				//走りアニメーションに遷移
		break;
	case CPlayerState::enPlayerStateAvoidance:
		m_currentState = &m_playerAvoidance;		//回避アニメーションに遷移
		break;
	case CPlayerState::enPlayerStateJump:
		m_currentState = &m_playerJump;				//ジャンプアニメーションに遷移	
		break;
	case CPlayerState::enPlayerStateRunJump:
		m_currentState = &m_playerJump;				//走りジャンプアニメーションに遷移	
		break;
	case CPlayerState::enPlayerStateAttack:
		m_currentState = &m_playerAttack;			//攻撃アニメーションに遷移
		break;
	case CPlayerState::enPlayerStateArrowAttack:	//弓の攻撃アニメーションに遷移
		m_currentState = &m_playerArrowAtack;
		break;
	case CPlayerState::enPlayerStateArrowShoot:		//弓の攻撃アニメーションに遷移
		m_currentState = &m_playerArrowShoot;
		break;
	case CPlayerState::enPlayerStateDamage:
		m_currentState = &m_playerDamege;			//ダメージアニメーションに遷移
		break;
	case CPlayerState::enPlayerStateDied:
		m_currentState = &m_playerDied;				//死亡アニメーションに遷移
		break;
	case CPlayerState::enPlayerStateWireMove:
		m_currentState = &m_playerWireMove;			//ワイヤーアニメーションに遷移
	}

	m_currentState->Init();
}

void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}