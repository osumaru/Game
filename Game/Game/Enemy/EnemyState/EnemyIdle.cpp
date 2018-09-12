#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool EnemyIdle::Start()
{
	//�ҋ@�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Idle);
	return true;
}

void EnemyIdle::Update()
{
	//�����Ȃ�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	m_timer += GameTime().GetDeltaFrameTime();
	if (m_timer >= 6.0f) {
		m_timer = 0.0f;
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}
