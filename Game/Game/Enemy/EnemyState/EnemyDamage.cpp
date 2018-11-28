#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../../UI/DamageNumber/DamageNumber.h"

void CEnemyDamage::Init()
{
	//ダメージアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enAnimation_Damage);

	//ダメージ数値を初期化
	m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
	m_damageNumber->Init(m_enemy);

	//ダメージを受けたフラグを戻す
	m_enemy->SetIsDamage(false);

	m_friction = 0.5f;
	//m_debugDamageCount++;
}

bool CEnemyDamage::Start()
{
	//初期化
	Init();

	return true;
}

void CEnemyDamage::Update()
{
	//ノックバックさせる
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 knockBack = m_enemy->GetPosition() - GetPlayer().GetPosition();
	knockBack.y = 0.0f;
	knockBack.Normalize();
	if (m_friction >= m_knockBackSpeed) {
		m_friction = m_knockBackSpeed;
	}
	knockBack *= m_knockBackSpeed - m_friction;
	m_friction += m_friction;
	moveSpeed.x = knockBack.x;
	moveSpeed.z = knockBack.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//プレイヤーとの距離を計算する
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();
	//攻撃範囲にいるかどうか判定
	bool isRange = m_enemy->CalucFanShape(10.0f, playerPos);

	if (m_enemy->GetStatus().hp <= 0) {
		//HPが無くなれば死亡
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
	else if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了している
		//if (m_debugDamageCount >= 2) {
		//	m_debugDamageCount = 0;
		//	//スタンする攻撃を受けた
		//	m_esm->ChangeState(CEnemyState::enState_Stan);
		//}
		if (isRange && length < 1.2f) {
			//近ければ攻撃
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else {
			//プレイヤーを追いかける
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
	}
	else if(m_enemy->IsDamage()) {
		//もう一度ダメージを受けたら初期化
		Init();
	}
}

void CEnemyDamage::Release()
{
	if (m_damageNumber != nullptr) {
		Delete(m_damageNumber);
		m_damageNumber = nullptr;
	}
}
