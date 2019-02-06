#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//移動しない
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);
	//エネミーが攻撃する
	m_enemy->Attack();
	
	//攻撃音
	const float AttackVolume = 0.3f;
	CSoundSource* AttackSound = New<CSoundSource>(0);
	AttackSound->Init("Assets/sound/Battle/WarrokEnemyAttackSE.wav");
	AttackSound->Play(false);
	AttackSound->SetVolume(AttackVolume);
	return true;
}

void CEnemyAttack::Update()
{
	if (m_enemy->GetIsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->GetAnimation().IsPlay()) {
		//アニメーションが終了している
		m_esm->ChangeState(CEnemyState::enState_AttackWait);
	}
}