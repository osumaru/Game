#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool CEnemyIdle::Start()
{
	//待機アニメーションを再生
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Idle, 0.3f);

	//タイマーを初期化
	m_timer = 0.0f;

	//移動しない
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);

	return true;
}

void CEnemyIdle::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_enemy->GetIsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (m_timer >= 6.0f) {
		//しばらくしたら歩き始める
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
	if (m_enemy->IsFind()) {
		//プレイヤーが視野内にいる
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
