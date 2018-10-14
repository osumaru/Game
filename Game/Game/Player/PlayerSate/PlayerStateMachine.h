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

		// 更新
		void Update();
			
		//ステートの切り替え
		void ChangeState(CPlayerState::EnPlayerState nextState);

		//解放
		void Release();

		//攻撃の状態を取得
		int GetAttackSate()
		{
			return m_AttackState;
		}
		//武器によって攻撃のモーションを変更させる
		void SetAttackState(const int setAttack)
		{
			m_AttackState = (CPlayerState::EnPlayerState)setAttack;
		}
		//現在のプレイヤーの状態を取得
		CPlayerState::EnPlayerState GetState()
		{
			return m_state;
		}
		//現在のプレイヤーの状態を取得
		const CPlayerState::EnPlayerState GetArrowState()
		{
			return m_ArrowAttackState;
		}
		void SetArrowAttackState(const int setAttack)
		{
			m_ArrowAttackState = (CPlayerState::EnPlayerState)setAttack;
		}


private:
	CPlayerState::EnPlayerState		m_state = CPlayerState::enState_Invald;				//プレイヤーのアニメーションの状態
	CPlayerState::EnPlayerState		m_AttackState = CPlayerState::enPlayerAttack;		//攻撃時のアニメーションの状態
	CPlayerState::EnPlayerState		m_ArrowAttackState = CPlayerState::enPlayerArrowAttack;	//弓矢での攻撃時のアニメーションの状態

	IPlayerState*					m_currentState = nullptr;
	CPlayerStand					m_playerStand;			//待機モーション
	CPlayerWalk						m_playerWalk;			//歩行モーション
	CPlayerRun						m_playerRun;			//走りモーション
	CPlayerAttack					m_playerAttack;			//攻撃モーション
	CPlayerDamage					m_playerDamege;			//ダメージモーション
	CPlayerDied						m_playerDied;			//死亡モーション
	CPlayerJump						m_playerJump;			//ジャンプモーション
	CPlayerAvoidance				m_playerAvoidance;		//回避モーション
	CPlayerArrowAttack				m_playerArrowAtack;		//弓での攻撃モーション
	CPlayerWireMove					m_playerWireMove;		//ワイヤーモーション
};

