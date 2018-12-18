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
#include "PlayerStun.h"
#include "PlayerWireAttack.h"
#include "PlayerSky.h"

class CPlayer;
class CPlayerGetter;

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

	void SetPlayer(CPlayer* player, CPlayerGetter* playerGetter)
	{
		m_playerStand.SetPlayer(player, playerGetter);
		m_playerWalk.SetPlayer(player, playerGetter);
		m_playerRun.SetPlayer(player, playerGetter);
		m_playerAttack.SetPlayer(player, playerGetter);
		m_playerDamage.SetPlayer(player, playerGetter);
		m_playerDied.SetPlayer(player, playerGetter);
		m_playerJump.SetPlayer(player, playerGetter);
		m_playerAvoidance.SetPlayer(player, playerGetter);
		m_playerArrowAttack.SetPlayer(player, playerGetter);
		m_playerArrowShoot.SetPlayer(player, playerGetter);
		m_playerWireMove.SetPlayer(player, playerGetter);
		m_playerStun.SetPlayer(player, playerGetter);
		m_playerWireAttack.SetPlayer(player, playerGetter);
		m_playerSky.SetPlayer(player, playerGetter);
	}

	//現在のステートを取得
	IPlayerState* GetCurrentState()
	{
		return m_currentState;
	}

	//指定したステートを取得
	IPlayerState* GetState(CPlayerState::EnPlayerState state)
	{
		return m_pStates[state];
	}


private:
	CPlayerState::EnPlayerState		m_state = (CPlayerState::EnPlayerState)-1;				//プレイヤーのアニメーションの状態
	
	IPlayerState*					m_currentState = nullptr;
	IPlayerState*					m_pStates[CPlayerState::enPlayerStateNum];
	CPlayerStand					m_playerStand;			//待機モーション
	CPlayerWalk						m_playerWalk;			//歩行モーション
	CPlayerRun						m_playerRun;			//走りモーション
	CPlayerAttack					m_playerAttack;			//攻撃モーション
	CPlayerDamage					m_playerDamage;			//ダメージモーション
	CPlayerDied						m_playerDied;			//死亡モーション
	CPlayerJump						m_playerJump;			//ジャンプモーション
	CPlayerAvoidance				m_playerAvoidance;		//回避モーション
	CPlayerArrowAttack				m_playerArrowAttack;	//弓での攻撃モーション
	CPlayerArrowShoot				m_playerArrowShoot;		//弓を放つモーション
	CPlayerWireMove					m_playerWireMove;		//ワイヤーモーション
	CPlayerStun						m_playerStun;			//スタン状態
	CPlayerWireAttack				m_playerWireAttack;		//ワイヤー攻撃モーション
	CPlayerSky						m_playerSky;			//空中にいる状態
};

