#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"

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
	CMatrix viewMatrix = GetGameCamera().GetViewMatrix();
	CMatrix projectionMatrix = GetGameCamera().GetProjectionMatrix();
	//ビュー変換
	CVector4 viewPosition = enemyPos;
	viewMatrix.Mul(viewPosition);
	//プロジェクション変換
	CVector4 projectionPosition = viewPosition;
	projectionMatrix.Mul(projectionPosition);
	projectionPosition = projectionPosition / projectionPosition.w;
	//スクリーン変換
	CVector2 screenPosition;
	screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * FrameBufferWidth() - (FrameBufferWidth() / 2.0f);
	screenPosition.y = (1.0f + projectionPosition.y) / 2.0f * FrameBufferHeight() - (FrameBufferHeight() / 4.0f);

	m_damageNumber.SetPosition(screenPosition);
	m_damageNumber.DamageCalculation(damage);

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

	CMatrix enemyWorldMatrix = m_enemy->GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();
	toPlayerPos.y = 0.0f;
	toPlayerPos.Normalize();
	float angle = enemyForward.Dot(toPlayerPos);
	angle = acosf(angle);

	if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了している
		if (fabsf(angle) < CMath::DegToRad(20.0f) && length < 2.0f) {
			//近ければ攻撃
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else if (m_enemy->IsFind()) {
			//発見されていたらプレイヤーを追いかける
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		else {
			//遠ければ歩き始める
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		//ダメージを受けたフラグを戻す
		m_enemy->SetIsDamage(false);
	}
	if (m_enemy->GetStatus().Hp <= 0) {
		//HPが無くなれば死亡
		m_esm->ChangeState(CEnemyState::enState_Death);
		//ダメージを受けたフラグを戻す
		m_enemy->SetIsDamage(false);
	}
}
