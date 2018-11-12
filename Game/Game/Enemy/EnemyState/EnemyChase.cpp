#include "stdafx.h"
#include "EnemyChase.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../PathFinding/PathFinding.h"

bool CEnemyChase::Start()
{
	//歩きアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Chase);

	return true;
}

void CEnemyChase::Update()
{
	//プレイヤーとの距離を計算
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	float length = toPlayerDir.Length();

	Move(length);

	//扇状の範囲に入っているか
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (m_enemy->IsDamage()){
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (isRange && length < 1.2f) {
		//プレイヤーと距離が近い且つ攻撃範囲にいる
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (!m_enemy->IsFind()) {
		//プレイヤーが離れたら戻っていく
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}

void CEnemyChase::Move(float length)
{
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	float speed = 3.0f;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyPos = m_enemy->GetPosition();
	CVector3 toPlayerDir = playerPos - enemyPos;
	if (length > 3.0f) {
		//経路探索する
		m_interval++;
		if (m_interval % 5 == 0) {
			std::vector<CVector2> root;
			CVector3 startPos = enemyPos;
			CVector3 targetPos = playerPos;
			g_pathFinding.FindRoot(root, { startPos.x, startPos.z }, { targetPos.x, targetPos.z });
			if (!root.empty()) {
				CVector3 rootPos = { root[0].x, 0.0f, root[0].y };
				CVector3 pos = enemyPos;
				pos.y = 0.0f;
				rootPos -= pos;
				rootPos.Normalize();
				moveSpeed.x = rootPos.x * 2.0f;
				moveSpeed.z = rootPos.z * 2.0f;
			}
		}
	}
	else {
		//プレイヤーを追いかける
		toPlayerDir.Normalize();
		toPlayerDir *= speed;
		moveSpeed.x = toPlayerDir.x;
		moveSpeed.z = toPlayerDir.z;
	}
	m_enemy->SetMoveSpeed(moveSpeed);
}
