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

		// 更新
		void Update();
			
		//ステートの切り替え
		void ChangeState(CPlayerState::EnPlayerState nextState);

		//解放
		void Release();



private:
	CPlayerState::EnPlayerState		m_state = CPlayerState::enState_Invald;
	IPlayerSate*					m_currentState = nullptr;
	CPlayerStand					m_playerStand;
	CPlayerWalk						m_playerWalk;
	CPlayerRun						m_playerRun;
	CPlayerAttack					m_playerAttack;
	CPlayerDamage					m_playerDamege;
	CPlayerDied						m_playerDied;
};

