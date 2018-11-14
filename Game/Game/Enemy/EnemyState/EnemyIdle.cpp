#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool CEnemyIdle::Start()
{
	//�ҋ@�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Idle);

	//�^�C�}�[��������
	m_timer = 0.0f;

	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 speed = CVector3::Zero;
	moveSpeed.x = speed.x;
	moveSpeed.z = speed.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	return true;
}

void CEnemyIdle::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_enemy->IsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (m_timer >= 6.0f) {
		//���΂炭����������n�߂�
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
	if (m_enemy->IsFind()) {
		//�v���C���[��������ɂ���
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
