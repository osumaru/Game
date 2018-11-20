#include "EnemyStan.h"
#include "../IEnemy.h"

bool CEnemyStan::Start()
{
	m_timer = 0.0f;

	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	return true;
}

void CEnemyStan::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_timer >= 3.0f) {
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
