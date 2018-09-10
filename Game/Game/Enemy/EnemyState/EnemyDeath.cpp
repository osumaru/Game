#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Itam/RecoveryItem.h"
#include "../../Itam/Money.h"

bool EnemyDeath::Start()
{
	//���S�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(EnemyState::enState_Death);
	return true;
}

void EnemyDeath::Update()
{
	//���S�A�j���[�V�������I�������񕜃A�C�e���Ƃ������o��
	if (!m_enemy->IsPlayAnimation()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
		recoveryItem->Init(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(0);
		money->Init(m_enemy->GetPosition());
		m_enemy->StateMachineRelease();
		Delete(m_enemy);
	}
}
