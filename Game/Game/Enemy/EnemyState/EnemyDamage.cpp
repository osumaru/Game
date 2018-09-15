#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"

bool CEnemyDamage::Start()
{
	//ダメージアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	//ダメージ計算
	m_enemy->DamageCalculation();

	return true;
}

void CEnemyDamage::Update()
{
	timer += GameTime().GetDeltaFrameTime();
	if (timer > 2.0f) {
		//ダメージ表示の描画をやめる
		m_enemy->DamageIndicateReset();
		timer = 0.0f;
	}

	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
}
