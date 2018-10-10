#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Itam/RecoveryItem.h"
#include "../../Itam/Money.h"

bool CEnemyDeath::Start()
{
	//���S�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Death);

	//�_���[�W�\���̕`�����߂�
	m_enemy->DamageIndicateReset();
	//�_���[�W���󂯂��t���O��߂�
	m_enemy->SetIsDamage(false);

	return true;
}

void CEnemyDeath::Update()
{
	//���S�A�j���[�V�������I�������񕜃A�C�e���Ƃ������o��
	if (!m_enemy->IsPlayAnimation()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
		recoveryItem->Init(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(0);
		money->Init(m_enemy->GetPosition());
		money->SetGold(m_enemy->GetStatus().Gold);
		m_enemy->StateMachineRelease();
		Delete(m_enemy);
	}
}
