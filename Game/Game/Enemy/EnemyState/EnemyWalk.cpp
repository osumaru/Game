#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"

bool CEnemyWalk::Start()
{
	//�����A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Walk);

	return true;
}

void CEnemyWalk::Update()
{
	if (m_enemy->IsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (!m_enemy->GetIsMove()) {
		//�ړ���܂ňړ�������~�܂�
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
	if (m_enemy->IsFind()) {
		//�v���C���[��������ɂ���
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
