#pragma once
#include"IPlayerState.h"
#include"PlayerState.h"
#include"PlayerStand.h"
#include"PlayerWalk.h"
#include"PlayerRun.h"

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



private:
	CPlayerState::EnPlayerState		m_state = CPlayerState::enState_Invald;
	IPlayerSate*					m_currentState = nullptr;
	CPlayerStand					m_playerStand;
	CPlayerWalk						m_playerWalk;
	CPlayerRun						m_playerRun;
};

