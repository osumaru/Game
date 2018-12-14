#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../../UI/DamageNumber/DamageNumber.h"

void CEnemyDamage::Init()
{
	//ダメージアニメーションを再生
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Damage, 0.3f);

	//ダメージ数値を初期化
	m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
	m_damageNumber->Init(m_enemy);

	//ダメージを受けたフラグを戻す
	m_enemy->SetIsDamage(false);

	m_friction = 0.5f;
	//スタンする攻撃であるか判定
	m_wasStanAttack = GetPlayer().GetStanAttack();
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
	else if (m_wasStanAttack)
	{
		//スタン状態になる
		m_esm->ChangeState(CEnemyState::enState_Stan);
	}
	else if (!m_enemy->GetAnimation().IsPlay()) {
		//アニメーションが終了している
		if (isRange && m_enemy->GetAttackLength()) {
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