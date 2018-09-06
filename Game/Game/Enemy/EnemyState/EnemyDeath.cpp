#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"

bool EnemyDeath::Start()
{
	m_enemy->SetAnimNum(EnemyState::enState_Death);
	return true;
}

void EnemyDeath::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Idle);
	}
}
