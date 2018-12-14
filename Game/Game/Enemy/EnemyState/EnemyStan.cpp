#include "EnemyStan.h"
#include "../IEnemy.h"
#include "../../UI/DamageNumber/DamageNumber.h"

bool CEnemyStan::Start()
{
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Down, 0.3f);

	m_timer = 0.0f;

	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	//ダメージを受けたフラグを戻す
	m_enemy->SetIsDamage(false);

	return true;
}

void CEnemyStan::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_enemy->IsDamage())
	{
		//ダメージ数値を初期化
		m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
		m_damageNumber->Init(m_enemy);
		//ダメージを受けたフラグを戻す
		m_enemy->SetIsDamage(false);
	}
	if (m_timer >= 3.0f) {
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
