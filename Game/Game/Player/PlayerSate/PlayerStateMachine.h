#pragma once
#include"IPlayerState.h"
#include"PlayerState.h"
#include"PlayerStand.h"
#include"PlayerWalk.h"
#include"PlayerRun.h"
#include "PlayerAttack.h"
#include "PlayerDamage.h"
#include "PlayerDied.h"

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



private:
	CPlayerState::EnPlayerState		m_state = CPlayerState::enState_Invald;			//�v���C���[�̃A�j���[�V�����̏��
	CPlayerState::EnPlayerState		m_AttackState = CPlayerState::enPlayerAttack;	//�U�����̃A�j���[�V�����̏��

	IPlayerSate*					m_currentState = nullptr;
	CPlayerStand					m_playerStand;
	CPlayerWalk						m_playerWalk;
	CPlayerRun						m_playerRun;
	CPlayerAttack					m_playerAttack;
	CPlayerDamage					m_playerDamege;
	CPlayerDied						m_playerDied;
};

