#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../../UI/DamageNumber/DamageNumber.h"

void CEnemyDamage::Init()
{
	//ダメージアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	m_damageNumber = New<CDamageNumber>(0);
	m_damageNumber->Init(m_enemy);
	debugNum++;

	//ダメージを受けたフラグを戻す
	m_enemy->SetIsDamage(false);

	//ノックバックさせる
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	m_knockBack = m_enemy->GetPosition() - GetPlayer().GetPosition();
	m_knockBack.y = 0.0f;
	m_knockBack.Normalize();
	m_knockBack *= m_knockBackSpeed;
	moveSpeed.x = m_knockBack.x;
	moveSpeed.z = m_knockBack.z;
	m_enemy->SetMoveSpeed(moveSpeed);
	m_enemy->SetMoveSpeed(CVector3::Zero);
}

bool CEnemyDamage::Start()
{
	//初期化
	Init();

	return true;
}

void CEnemyDamage::Update()
{
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 knockBack = moveSpeed;
	knockBack *= GameTime().GetDeltaFrameTime() * 3.0f;
	moveSpeed -= knockBack;
	//m_enemy->SetMoveSpeed(moveSpeed);

	//プレイヤーとの距離を計算する
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();
	//扇状の範囲にいるかどうか判定
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (m_enemy->GetStatus().Hp <= 0) {
		//HPが無くなれば死亡
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
	else if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了している
		if (isRange  && length < 2.0f) {
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
		debugNum--;
		Delete(m_damageNumber);
		m_damageNumber = nullptr;
	}
}
