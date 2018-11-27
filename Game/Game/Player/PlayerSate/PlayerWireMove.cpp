#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

void CPlayerWireMove::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireMove, 0.25f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();
	m_accel = 0.0f;
	m_moveSpeed = 0.0f;
}

void CPlayerWireMove::Update()
{
	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
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
		m_pPlayerGetter->SetMoveSpeed(toMovePos);
		m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
	}
	else {
		isMoveEnd = true;
	}

	if (isMoveEnd) {
		//移動が終わった
		GetPlayer().GetWireAction().SetIsWireMove(false);
		std::list<IEnemy*> enemyList = GetSceneGame().GetMap()->GetEnemyList();
		switch(m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateWireAttack);
			//移動し終わったら敵のフラグを戻してやる
			for (auto& enemy : enemyList)
			{
				if (enemy->IsWireHit()) {
					//ワイヤーが当たっていたらダメージ
					enemy->SetIsDamage(true);
				}
				enemy->SetIsWireHit(false);
			}
			break;
		case CWireAction::enStateMap:
			if (toMovePos.y > 0.0f)
			{
				m_pPlayerGetter->SetMoveSpeed(toMovePos);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
			}
			else
			{
				m_pPlayerGetter->SetPosition(m_movePosition);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
				m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationLanding);
			}
			break;
		}
	}
}
