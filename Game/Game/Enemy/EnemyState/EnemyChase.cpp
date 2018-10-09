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
	if (m_enemy->IsWireHit()) {
		//ワイヤーが当たっていたら何もしない
		return;
	}

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

	CMatrix enemyWorldMatrix = m_enemy->GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	toPlayerPos.y = 0.0f;
	toPlayerPos.Normalize();
	float angle = enemyForward.Dot(toPlayerPos);
	angle = acosf(angle);

	if (m_enemy->IsDamage()){
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (fabsf(angle) < CMath::DegToRad(30.0f) && length < 2.0f) {
		//プレイヤーと距離が近い
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (!m_enemy->IsFind()) {
		//プレイヤーが離れたら戻っていく
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}
