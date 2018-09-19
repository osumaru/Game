#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool CEnemyIdle::Start()
{
	//�ҋ@�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Idle);
	return true;
}

void CEnemyIdle::Update()
{
	//�����Ȃ�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	m_timer += GameTime().GetDeltaFrameTime();

	if (m_enemy->IsDamage()) {
		//�_���[�W���󂯂�
		m_timer = 0.0f;
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (m_timer >= 6.0f) {
		//���΂炭����������n�߂�
		m_timer = 0.0f;
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
	if (m_enemy->IsFind()) {
		//�v���C���[��������ɂ���
		m_timer = 0.0f;
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
