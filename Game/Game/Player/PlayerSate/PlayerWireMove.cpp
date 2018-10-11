#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

bool CPlayerWireMove::Start()
{
	m_movePosition = GetPlayer().GetWirePosition();

	return true;
}

void CPlayerWireMove::Update()
{
	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toMovePos = m_movePosition - playerPos;

	float length = toMovePos.Length();
	if (length > 1.5f) {
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
			CVector3 enemyPos = enemy->GetPosition();
			CVector3 toMovePos = m_movePosition - enemyPos;
			float length = toMovePos.Length();
			if (length < 0.1f) {
				enemy->SetIsWireHit(false);
			}
		}
	}

	if (isMoveEnd) {
		GetPlayer().SetIsWireMove(false);
		//移動が終わった
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}
}
