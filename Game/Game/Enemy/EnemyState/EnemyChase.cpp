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
	//プレイヤーとの距離を計算
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	float length = toPlayerDir.Length();

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
