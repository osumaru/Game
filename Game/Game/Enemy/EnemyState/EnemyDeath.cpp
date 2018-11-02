#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Item/RecoveryItem.h"
#include "../../Item/Money.h"
#include "../../Item/TreasureChest.h"

bool CEnemyDeath::Start()
{
	//���S�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Death);

	return true;
}

void CEnemyDeath::Update()
{
	//���S�A�j���[�V�������I�������񕜃A�C�e���Ƃ������o��
	if (!m_enemy->IsPlayAnimation()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
		recoveryItem->Pop(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(0);
		money->Pop(m_enemy->GetPosition());
		money->SetGold(m_enemy->GetStatus().Gold);
		CTreasureChest* treasureChest = New<CTreasureChest>(0);
		treasureChest->Pop(m_enemy->GetPosition());
		m_enemy->StateMachineRelease();
		Delete(m_enemy);
	}
}
