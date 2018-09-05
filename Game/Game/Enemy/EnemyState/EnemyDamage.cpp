#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"

bool EnemyDamage::Start()
{
	m_enemy->SetAnimNum(EnemyState::enState_Damage);
	return true;
}

void EnemyDamage::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Death);
	}
}
