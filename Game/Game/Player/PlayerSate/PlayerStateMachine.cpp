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
	case CPlayerState::enPlayerDamage:
		m_currentState = &m_playerDamege;	//�_���[�W�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerDied:
		m_currentState = &m_playerDied;		//���S�A�j���[�V�����ɑJ��
		break;
	case CPlayerState::enPlayerWireMove:
		m_currentState = &m_playerWireMove;	//���C���[�A�j���[�V�����ɑJ��
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