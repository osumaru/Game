#include "stdafx.h"
#include "EnemyWalk.h"
#include "Zombie.h"

bool EnemyWalk::Start()
{
	return true;
}

void EnemyWalk::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Idle);
	}
}
