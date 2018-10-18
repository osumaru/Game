#include "stdafx.h"
#include "EnemyIdle.h"
#include "../IEnemy.h"

bool CEnemyIdle::Start()
{
	//待機アニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Idle);

	//タイマーを初期化
	m_timer = 0.0f;

	return true;
}

void CEnemyIdle::Update()
{
	//動かない
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	m_timer += GameTime().GetDeltaFrameTime();

	//if (m_enemy->IsDamage()) {
	//	//ダメージを受けた
	//	m_esm->ChangeState(CEnemyState::enState_Damage);
	//}
	//if (m_timer >= 6.0f) {
	//	//しばらくしたら歩き始める
	//	m_esm->ChangeState(CEnemyState::enState_Walk);
	//}
	//if (m_enemy->IsFind()) {
	//	//プレイヤーが視野内にいる
	//	m_esm->ChangeState(CEnemyState::enState_Chase);
	//}
}
