#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"

bool EnemyAttack::Start()
{
	m_enemy->SetAnimNum(EnemyState::enState_Attack);
	return true;
}

void EnemyAttack::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Damage);
	}
}
