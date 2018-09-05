#include "stdafx.h"
#include "EnemyIdle.h"
#include "Zombie.h"

bool EnemyIdle::Start()
{
	return true;
}

void EnemyIdle::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Walk);
	}
}
