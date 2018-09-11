#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool EnemyIdle::Start()
{
	//待機アニメーションを再生
	m_enemy->PlayAnimation(EnemyState::enState_Idle);
	return true;
}

void EnemyIdle::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Walk);
	}
}
