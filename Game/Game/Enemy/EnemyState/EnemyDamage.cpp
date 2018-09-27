#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../EnemyGroup.h"

bool CEnemyDamage::Start()
{
	

	//ダメージアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	//ダメージ計算
	int playerStrength = GetPlayer().GetStatus().Strength;
	int enemyDefence = m_enemy->GetStatus().Defense;
	int damage = playerStrength - enemyDefence;
	m_enemy->HpDamage(damage);
	CVector3 enemyPos = m_enemy->GetPosition();
	m_enemy->SetDamagePos({ enemyPos.x, enemyPos.y });
	m_enemy->DamageCalculation(damage);

	return true;
}

void CEnemyDamage::Update()
{
	//ダメージを受けているときは動かない
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();

	if (!m_enemy->IsPlayAnimation()) {
		if (length < 2.0f) {
			//近ければ攻撃
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else if (m_enemy->IsFind()) {
			//アニメーションが終了していればプレイヤーを追いかける
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		else {
			//遠ければ歩き始める
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		//ダメージ表示の描画をやめる
		m_enemy->DamageIndicateReset();
		//ダメージを受けたフラグを戻す
		m_enemy->SetIsDamage(false);
	}
	if (m_enemy->GetStatus().Hp <= 0) {
		//HPが無くなれば死亡
		m_esm->ChangeState(CEnemyState::enState_Death);
		//ダメージ表示の描画をやめる
		m_enemy->DamageIndicateReset();
	}
}
