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
		//�����X�e�[�g�Ȃ�Ԃ�
		return;
	}

	//���݂̃X�e�[�g���Q�[���I�u�W�F�N�g����폜
	if (m_currentState != nullptr) {
		Delete(m_currentState);
	}

	m_state = nextState;

	switch (m_state) {
	case CPlayerState::enPlayerStand:
		m_currentState = &m_playerStand;
		break;
	case CPlayerState::enPlayerWalk:
		m_currentState = &m_playerWalk;
		break;
	case CPlayerState::enPlayerRun:
		m_currentState = &m_playerRun;
		break;
	/*case CPlayerState::enState_Attack:
		m_currentState = &m_enemyAttack;
		break;
	case CPlayerState::enState_Damage:
		m_currentState = &m_enemyDamage;
		break;
	case CPlayerState::enState_Death:
		m_currentState = &m_enemyDeath;
		break;*/
	}

	//�ύX�����X�e�[�g���Q�[���I�u�W�F�N�g�ɒǉ�
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