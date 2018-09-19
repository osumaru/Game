#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyDamage::Start()
{
	//ダメージを受けたフラグを戻す
	m_enemy->SetIsDamage(false);

	//ダメージアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	//ダメージ計算
	m_enemy->DamageCalculation();

	return true;
}

void CEnemyDamage::Update()
{
	//ダメージを受けているときは動かない
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	timer += GameTime().GetDeltaFrameTime();
	if (timer > 2.0f) {
		//ダメージ表示の描画をやめる
		m_enemy->DamageIndicateReset();
		timer = 0.0f;
	}

	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();

	if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了していればプレイヤーを追いかける
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
