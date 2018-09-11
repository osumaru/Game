#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"

bool EnemyDamage::Start()
{
	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(EnemyState::enState_Damage);

	//�_���[�W�v�Z
	m_enemy->DamageCalculation();

	return true;
}

void EnemyDamage::Update()
{
	timer += GameTime().GetDeltaFrameTime();
	if (timer > 2.0f) {
		//�_���[�W�\���̕`�����߂�
		m_enemy->DamageIndicateReset();
		timer = 0.0f;
	}

	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Death);
	}
}
