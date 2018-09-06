#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"

bool EnemyWalk::Start()
{
	m_enemy->SetAnimNum(EnemyState::enState_Walk);
	return true;
}

void EnemyWalk::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Attack);
	}
}
