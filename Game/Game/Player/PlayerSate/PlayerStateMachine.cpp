#include "stdafx.h"
#include "PlayerStateMachine.h"


void CPlayerStateMachine::Init()
{
	SetState(CPlayerState::enPlayerStateStand);
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
		m_currentState = &m_playerStand;			//�ҋ@�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateWalk:
		m_currentState = &m_playerWalk;				//���s�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateRun:
		m_currentState = &m_playerRun;				//����A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateAvoidance:
		m_currentState = &m_playerAvoidance;		//����A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateJump:
		m_currentState = &m_playerJump;				//�W�����v�A�j���[�V�����ɑJ��	
		break;
	case CPlayerState::enPlayerStateRunJump:
		m_currentState = &m_playerJump;				//����W�����v�A�j���[�V�����ɑJ��	
		break;
	case CPlayerState::enPlayerStateAttack:
		m_currentState = &m_playerAttack;			//�U���A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateArrowAttack:	//�|�̍U���A�j���[�V�����ɑJ��
		m_currentState = &m_playerArrowAtack;
		break;
	case CPlayerState::enPlayerStateArrowShoot:		//�|�̍U���A�j���[�V�����ɑJ��
		m_currentState = &m_playerArrowShoot;
		break;
	case CPlayerState::enPlayerStateDamage:
		m_currentState = &m_playerDamege;			//�_���[�W�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateDied:
		m_currentState = &m_playerDied;				//���S�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerStateWireMove:
		m_currentState = &m_playerWireMove;			//���C���[�A�j���[�V�����ɑJ��
	}

	m_currentState->Init();
}

void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}