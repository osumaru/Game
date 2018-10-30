#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

void CPlayerWireMove::Init()
{
	GetPlayer().SetPlayerAnimation(enPlayerAnimationWireMove, 0.1f);
	m_movePosition = GetPlayer().GetWirePosition();
}

void CPlayerWireMove::Update()
{
	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toMovePos = m_movePosition - playerPos;

	float length = toMovePos.Length();
	if (length > 2.0f) {
		//敵との距離が離れていれば移動先に進む
		toMovePos.Normalize();
		toMovePos *= m_speed;
		GetPlayer().SetMoveSpeed(toMovePos);
	}
	else {
		isMoveEnd = true;
	}

	if (isMoveEnd) {
		//移動し終わったら敵のフラグを戻してやる
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		for (auto& enemy : enemyList)
		{
			enemy->SetIsWireHit(false);
		}
	}

	if (isMoveEnd) {
		GetPlayer().SetIsWireMove(false);
		//移動が終わった
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}
