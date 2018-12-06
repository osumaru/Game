#include "stdafx.h"
#include "PlayerStateMachine.h"


void CPlayerStateMachine::Init()
{
	SetState(CPlayerState::enPlayerStateStand);
	m_pStates[CPlayerState::enPlayerStateStand] = &m_playerStand;	
	m_pStates[CPlayerState::enPlayerStateWalk] = &m_playerWalk;
	m_pStates[CPlayerState::enPlayerStateRun] = &m_playerRun;
	m_pStates[CPlayerState::enPlayerStateAvoidance] = &m_playerAvoidance;
	m_pStates[CPlayerState::enPlayerStateJump] = &m_playerJump;
	m_pStates[CPlayerState::enPlayerStateRunJump] = &m_playerJump;
	m_pStates[CPlayerState::enPlayerStateAttack] = &m_playerAttack;
	m_pStates[CPlayerState::enPlayerStateArrowAttack] = &m_playerArrowAttack;
	m_pStates[CPlayerState::enPlayerStateArrowShoot] = &m_playerArrowShoot;
	m_pStates[CPlayerState::enPlayerStateDamage] = &m_playerDamage;
	m_pStates[CPlayerState::enPlayerStateDied] = &m_playerDied;
	m_pStates[CPlayerState::enPlayerStateWireMove] = &m_playerWireMove;
	m_pStates[CPlayerState::enPlayerStateStun] = &m_playerStun;
	m_pStates[CPlayerState::enPlayerStateWireAttack] = &m_playerWireAttack;
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
		m_currentState = &m_playerStand;			//待機ステートに遷移
		break;
	case CPlayerState::enPlayerStateWalk:
		m_currentState = &m_playerWalk;				//歩行ステートに遷移
		break;
	case CPlayerState::enPlayerStateRun:
		m_currentState = &m_playerRun;				//走りステートに遷移
		break;
	case CPlayerState::enPlayerStateAvoidance:
		m_currentState = &m_playerAvoidance;		//回避ステートに遷移
		break;
	case CPlayerState::enPlayerStateJump:
		m_currentState = &m_playerJump;				//ジャンプステートに遷移	
		break;
	case CPlayerState::enPlayerStateRunJump:
		m_currentState = &m_playerJump;				//走りジャンプステートに遷移	
		break;
	case CPlayerState::enPlayerStateAttack:
		m_currentState = &m_playerAttack;			//攻撃ステートに遷移
		break;
	case CPlayerState::enPlayerStateArrowAttack:	//弓の攻撃ステートに遷移
		m_currentState = &m_playerArrowAttack;
		break;
	case CPlayerState::enPlayerStateArrowShoot:		//弓の攻撃ステートに遷移
		m_currentState = &m_playerArrowShoot;
		break;
	case CPlayerState::enPlayerStateDamage:
		m_currentState = &m_playerDamage;			//ダメージステートに遷移
		break;
	case CPlayerState::enPlayerStateDied:
		m_currentState = &m_playerDied;				//死亡ステートに遷移
		break;
	case CPlayerState::enPlayerStateWireMove:
		m_currentState = &m_playerWireMove;			//ワイヤーステートに遷移
		break;
	case CPlayerState::enPlayerStateStun:
		m_currentState = &m_playerStun;			//ワイヤーステートに遷移
		break;
	case CPlayerState::enPlayerStateWireAttack:
		m_currentState = &m_playerWireAttack;	//ワイヤー攻撃ステートに遷移
		break;
	}

	m_currentState->Init();
}

void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}