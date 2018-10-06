#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

bool CPlayerWireMove::Start()
{
	float minLength = FLT_MAX;
	std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
	//ワイヤーを飛ばす先を決める
	for (auto& enemy : enemyList)
	{
		CVector3 enemyPos = enemy->GetPosition();
		CVector3 toEnemyPos = enemyPos - GetPlayer().GetPosition();
		float length = toEnemyPos.Length();
		if (minLength > length) {
			minLength = length;
			//一番近い敵の位置を移動先とする
			m_movePosition = enemyPos;
		}
	}

	//一番近い敵にワイヤーが当たったフラグを設定する
	for (auto& enemy : enemyList) 
	{
		CVector3 enemyPos = enemy->GetPosition();
		CVector3 toMovePos = m_movePosition - enemyPos;
		float length = toMovePos.Length();
		if (length < 0.1f) {
			enemy->SetIsWireHit(true);
		}
	}

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
		//移動が終わった
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}
}
