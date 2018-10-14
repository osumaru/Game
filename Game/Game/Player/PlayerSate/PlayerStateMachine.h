#pragma once
#include"IPlayerState.h"
#include"PlayerState.h"
#include"PlayerStand.h"
#include"PlayerWalk.h"
#include"PlayerRun.h"
#include "PlayerAttack.h"
#include "PlayerArrowAttack.h"
#include "PlayerDamage.h"
#include "PlayerDied.h"
#include "PlayerJump.h"
#include "PlayerAvoidance.h"
#include "PlayerWireMove.h"

class CPlayerStateMachine	:public IGameObject
{
public:
	CPlayerStateMachine();
		~CPlayerStateMachine();

		bool Start();

		// �X�V
		void Update();
			
		//�X�e�[�g�̐؂�ւ�
		void ChangeState(CPlayerState::EnPlayerState nextState);

		//���
		void Release();

		//�U���̏�Ԃ��擾
		int GetAttackSate()
		{
			return m_AttackState;
		}
		//����ɂ���čU���̃��[�V������ύX������
		void SetAttackState(const int setAttack)
		{
			m_AttackState = (CPlayerState::EnPlayerState)setAttack;
		}
		//���݂̃v���C���[�̏�Ԃ��擾
		CPlayerState::EnPlayerState GetState()
		{
			return m_state;
		}
		//���݂̃v���C���[�̏�Ԃ��擾
		const CPlayerState::EnPlayerState GetArrowState()
		{
			return m_ArrowAttackState;
		}
		void SetArrowAttackState(const int setAttack)
		{
			m_ArrowAttackState = (CPlayerState::EnPlayerState)setAttack;
		}


private:
	CPlayerState::EnPlayerState		m_state = CPlayerState::enState_Invald;				//�v���C���[�̃A�j���[�V�����̏��
	CPlayerState::EnPlayerState		m_AttackState = CPlayerState::enPlayerAttack;		//�U�����̃A�j���[�V�����̏��
	CPlayerState::EnPlayerState		m_ArrowAttackState = CPlayerState::enPlayerArrowAttack;	//�|��ł̍U�����̃A�j���[�V�����̏��

	IPlayerState*					m_currentState = nullptr;
	CPlayerStand					m_playerStand;			//�ҋ@���[�V����
	CPlayerWalk						m_playerWalk;			//���s���[�V����
	CPlayerRun						m_playerRun;			//���胂�[�V����
	CPlayerAttack					m_playerAttack;			//�U�����[�V����
	CPlayerDamage					m_playerDamege;			//�_���[�W���[�V����
	CPlayerDied						m_playerDied;			//���S���[�V����
	CPlayerJump						m_playerJump;			//�W�����v���[�V����
	CPlayerAvoidance				m_playerAvoidance;		//������[�V����
	CPlayerArrowAttack				m_playerArrowAtack;		//�|�ł̍U�����[�V����
	CPlayerWireMove					m_playerWireMove;		//���C���[���[�V����
};

