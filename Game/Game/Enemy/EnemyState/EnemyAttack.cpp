#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//�ړ����Ȃ�
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);
	//�G�l�~�[���U������
	m_enemy->Attack();

	return true;
}

void CEnemyAttack::Update()
{
	if (m_enemy->GetIsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->GetAnimation().IsPlay()) {
		//�A�j���[�V�������I�����Ă���
		m_esm->ChangeState(CEnemyState::enState_AttackWait);
	}
}