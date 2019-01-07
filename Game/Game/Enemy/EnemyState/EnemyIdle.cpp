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

	//if (m_timer > 10.0f)
	//{
	//	m_speed *= -1.0f;
	//	m_timer = 0.0f;
	//}

	//CVector3 moveSpeed = CVector3::Zero;
	//moveSpeed.x = m_speed;
	//m_enemy->SetMoveSpeed(moveSpeed);

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
