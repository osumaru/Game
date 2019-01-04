#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool CEnemyIdle::Start()
{
	//�ҋ@�A�j���[�V�������Đ�
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Idle, 0.3f);

	//�^�C�}�[��������
	m_timer = 0.0f;

	//�ړ����Ȃ�
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);

	return true;
}

void CEnemyIdle::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_enemy->GetIsDamage()) {
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
