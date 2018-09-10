#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Itam/RecoveryItem.h"
#include "../../Itam/Money.h"

bool EnemyDeath::Start()
{
	//死亡アニメーションを再生
	m_enemy->PlayAnimation(EnemyState::enState_Death);
	return true;
}

void EnemyDeath::Update()
{
	//死亡アニメーションが終わったら回復アイテムとお金を出す
	if (!m_enemy->IsPlayAnimation()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
		recoveryItem->Init(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(0);
		money->Init(m_enemy->GetPosition());
		m_enemy->StateMachineRelease();
		Delete(m_enemy);
	}
}
