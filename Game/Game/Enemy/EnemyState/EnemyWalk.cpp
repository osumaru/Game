#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"

bool CEnemyWalk::Start()
{
	//歩きアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Walk);

	return true;
}

void CEnemyWalk::Update()
{
	if (m_enemy->IsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (!m_enemy->GetIsMove()) {
		//移動先まで移動したら止まる
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
	if (m_enemy->IsFind()) {
		//プレイヤーが視野内にいる
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
