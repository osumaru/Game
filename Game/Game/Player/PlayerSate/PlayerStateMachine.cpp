#include "stdafx.h"
#include "PlayerStateMachine.h"


CPlayerStateMachine::CPlayerStateMachine()
{


}


CPlayerStateMachine::~CPlayerStateMachine()
{

}

bool CPlayerStateMachine::Start()
{
	ChangeState(CPlayerState::enPlayerStand);
	return true;
}


void CPlayerStateMachine::ChangeState(CPlayerState::EnPlayerState nextState)
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
	case CPlayerState::enPlayerDamage:
		m_currentState = &m_playerDamege;	//ダメージアニメーションに遷移
		break;
	case CPlayerState::enPlayerDied:
		m_currentState = &m_playerDied;		//死亡アニメーションに遷移
		break;
	case CPlayerState::enPlayerWireMove:
		m_currentState = &m_playerWireMove;	//ワイヤーアニメーションに遷移
	}

	//変更したステートをゲームオブジェクトに追加
	Add(m_currentState, 0);
}

void CPlayerStateMachine::Update()
{	
}

void CPlayerStateMachine::Release()
{
	Delete(m_currentState);
	Delete(this);
}