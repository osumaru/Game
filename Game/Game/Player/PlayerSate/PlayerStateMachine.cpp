#include "stdafx.h"
#include "PlayerStateMachine.h"


void CPlayerStateMachine::Init()
{
	ChangeState(CPlayerState::enPlayerStand);
}


void CPlayerStateMachine::ChangeState(CPlayerState::EnPlayerState nextState)
{
	if (m_state == nextState) {
		//�����X�e�[�g�Ȃ�Ԃ�
		return;
	}

	m_state = nextState;

	switch (m_state) {
	case CPlayerState::enPlayerStand:
		m_currentState = &m_playerStand;	//�ҋ@�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerWalk:
		m_currentState = &m_playerWalk;		//���s�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerRun:
		m_currentState = &m_playerRun;		//����A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerAvoidance:
		m_currentState = &m_playerAvoidance;//����A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerJump:
		m_currentState = &m_playerJump;		//�W�����v�A�j���[�V�����ɑJ��	
		break;
	case CPlayerState::enPlayerRunJump:
		m_currentState = &m_playerJump;		//����W�����v�A�j���[�V�����ɑJ��	
		break;
	case CPlayerState::enPlayerAttack:
		m_currentState = &m_playerAttack;	//�U���A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerArrowAttack:	//�|�̍U���A�j���[�V�����ɑJ��
		m_currentState = &m_playerArrowAtack;
		break;
	case CPlayerState::enPlayerArrowShoot:	//�|�̍U���A�j���[�V�����ɑJ��
		m_currentState = &m_playerArrowShoot;
		break;
	case CPlayerState::enPlayerDamage:
		m_currentState = &m_playerDamege;	//�_���[�W�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerDied:
		m_currentState = &m_playerDied;		//���S�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerWireMove:
		m_currentState = &m_playerWireMove;	//���C���[�A�j���[�V�����ɑJ��
	}

	m_currentState->Init();
}

void CPlayerStateMachine::Update()
{
	m_currentState->Update();
}