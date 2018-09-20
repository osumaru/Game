#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyDamage::Start()
{
	//�_���[�W���󂯂��t���O��߂�
	m_enemy->SetIsDamage(false);

	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	//�_���[�W�v�Z
	m_enemy->DamageCalculation();

	return true;
}

void CEnemyDamage::Update()
{
	//�_���[�W���󂯂Ă���Ƃ��͓����Ȃ�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	timer += GameTime().GetDeltaFrameTime();
	if (timer > 2.0f) {
		//�_���[�W�\���̕`�����߂�
		m_enemy->DamageIndicateReset();
		timer = 0.0f;
	}

	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();

	if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���΃v���C���[��ǂ�������
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
