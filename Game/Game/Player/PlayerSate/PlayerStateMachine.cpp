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
		//�����X�e�[�g�Ȃ�Ԃ�
		return;
	}

	m_state = nextState;

	switch (m_state) {
	case CPlayerState::enPlayerStateStand:
		m_currentState = &m_playerStand;			//�ҋ@�X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateWalk:
		m_currentState = &m_playerWalk;				//���s�X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateRun:
		m_currentState = &m_playerRun;				//����X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateAvoidance:
		m_currentState = &m_playerAvoidance;		//����X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateJump:
		m_currentState = &m_playerJump;				//�W�����v�X�e�[�g�ɑJ��	
		break;
	case CPlayerState::enPlayerStateRunJump:
		m_currentState = &m_playerJump;				//����W�����v�X�e�[�g�ɑJ��	
		break;
	case CPlayerState::enPlayerStateAttack:
		m_currentState = &m_playerAttack;			//�U���X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateArrowAttack:	//�|�̍U���X�e�[�g�ɑJ��
		m_currentState = &m_playerArrowAttack;
		break;
	case CPlayerState::enPlayerStateArrowShoot:		//�|�̍U���X�e�[�g�ɑJ��
		m_currentState = &m_playerArrowShoot;
		break;
	case CPlayerState::enPlayerStateDamage:
		m_currentState = &m_playerDamage;			//�_���[�W�X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateDied:
		m_currentState = &m_playerDied;				//���S�X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateWireMove:
		m_currentState = &m_playerWireMove;			//���C���[�X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateStun:
		m_currentState = &m_playerStun;			//���C���[�X�e�[�g�ɑJ��
		break;
	case CPlayerState::enPlayerStateWireAttack:
		m_currentState = &m_playerWireAttack;	//���C���[�U���X�e�[�g�ɑJ��
		break;
	}

	m_currentState->Init();
}

void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}