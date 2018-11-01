#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Itam/RecoveryItem.h"
#include "../../Itam/Money.h"

bool CEnemyDeath::Start()
{
	//死亡アニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Death);

	return true;
}

void CEnemyDeath::Update()
{
	//死亡アニメーションが終わったら回復アイテムとお金を出す
	if (!m_enemy->IsPlayAnimation()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
		recoveryItem->Pop(m_enemy->GetPosition());
		//recoveryItem->Init(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(0);
		money->Init(m_enemy->GetPosition());
		money->SetGold(m_enemy->GetStatus().Gold);
		m_enemy->StateMachineRelease();
		Delete(m_enemy);
	}
}
