#pragma once
#include "PlayerState.h"
#include "PlayerStateCommon.h"
#include "PlayerStand.h"
#include "PlayerWalk.h"
#include "PlayerRun.h"
#include "PlayerAttack.h"
#include "PlayerArrowAttack.h"
#include "PlayerDamage.h"
#include "PlayerDied.h"
#include "PlayerJump.h"
#include "PlayerAvoidance.h"
#include "PlayerArrowShoot.h"
#include "PlayerWireMove.h"

class CPlayer;

class CPlayerStateMachine
{
public:
	void Init();

	// 更新
	void Update();
			
	//ステートの切り替え
	void SetState(CPlayerState::EnPlayerState nextState);

	//現在のプレイヤーの状態を取得
	CPlayerState::EnPlayerState GetState() const
	{
		return m_state;
	}

	void SetPlayer(CPlayer* player)
	{
		m_playerStand.SetPlayer(player);
		m_playerWalk.SetPlayer(player);
		m_playerRun.SetPlayer(player);
		m_playerAttack.SetPlayer(player);
		m_playerDamege.SetPlayer(player);
		m_playerDied.SetPlayer(player);
		m_playerJump.SetPlayer(player);
		m_playerAvoidance.SetPlayer(player);
		m_playerArrowAtack.SetPlayer(player);
		m_playerArrowShoot.SetPlayer(player);
		m_playerWireMove.SetPlayer(player);
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
	CPlayerArrowShoot				m_playerArrowShoot;		//弓を放つモーション
	CPlayerWireMove					m_playerWireMove;		//ワイヤーモーション
};

