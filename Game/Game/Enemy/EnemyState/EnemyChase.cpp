#include "stdafx.h"
#include "EnemyChase.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyChase::Start()
{
	//歩きアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Chase);

	return true;
}

void CEnemyChase::Update()
{
	//移動速度を取得
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	//プレイヤーを追いかける
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	float length = toPlayerDir.Length();
	toPlayerDir.Normalize();
	toPlayerDir *= m_speed;
	moveSpeed.x = toPlayerDir.x;
	moveSpeed.z = toPlayerDir.z;
	//移動速度を設定
	m_enemy->SetMoveSpeed(moveSpeed);

	if (m_enemy->IsDamage()){
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (length < 2.0f) {
		//プレイヤーと距離が近い
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (!m_enemy->IsFind()) {
		//プレイヤーが離れたら戻っていく
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}
