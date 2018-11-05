#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
#include "../WireAction.h"

void CPlayerWireMove::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationWireMove, 0.1f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();
	m_accel = 0.0f;
	m_moveSpeed = 0.0f;
}

void CPlayerWireMove::Update()
{
	CVector3 playerPos = m_pPlayer->GetPosition();
	bool isMoveEnd = false;
	CVector3 toMovePos = m_movePosition - playerPos;

	float length = toMovePos.Length();
	toMovePos.Normalize();
	m_accel += 0.3f;
	m_moveSpeed += m_accel;
	if (m_speed < m_moveSpeed)
	{
		m_moveSpeed = m_speed;
	}
	toMovePos *= m_moveSpeed;
	float range = 2.0f;

	switch (m_pPlayer->GetWireAction().GetState())
	{
	case CWireAction::enStateEnemy:
		range = 2.0f;
		break;
	case CWireAction::enStateMap:
		range = 1.0f;
		break;
	}
	if (length > range) {
		//目標との距離が離れていれば移動先に進む
		GetPlayer().SetMoveSpeed(toMovePos);
		m_pPlayer->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
	}
	else {
		m_pPlayer->GetWireAction().SetIsWireMove(false);
		isMoveEnd = true;
	}

	if (isMoveEnd) {
		//移動が終わった
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		switch (m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			//移動し終わったら敵のフラグを戻してやる
			for (auto& enemy : enemyList)
			{
				enemy->SetIsWireHit(false);
			}
			break;
		case CWireAction::enStateMap:
			if (toMovePos.y > 0.0f)
			{
				m_pPlayer->SetMoveSpeed(toMovePos);
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateJump);
			}
			else
			{
				m_pPlayer->SetPosition(m_movePosition);
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
				m_pPlayer->PlayAnimation(enPlayerAnimationLanding);
			}
			break;
		}

	}
}
