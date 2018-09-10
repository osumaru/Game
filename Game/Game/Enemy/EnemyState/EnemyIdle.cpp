#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool EnemyIdle::Start()
{
	//�ҋ@�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(EnemyState::enState_Idle);
	return true;
}

void EnemyIdle::Update()
{
	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Walk);
	}
}
