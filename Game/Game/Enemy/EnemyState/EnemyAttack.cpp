#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//移動しない
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);

	//攻撃アニメーションを再生
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Attack, 0.3f);

	//m_enemy->Attack();

	return true;
}

void CEnemyAttack::Update()
{
	if (m_enemy->IsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->GetAnimation().IsPlay()) {
		//アニメーションが終了している
		m_esm->ChangeState(CEnemyState::enState_AttackWait);
	}
}