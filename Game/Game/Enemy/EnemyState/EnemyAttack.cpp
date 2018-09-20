#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//攻撃アニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Attack);

	//攻撃するときは移動をやめる
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	return true;
}

void CEnemyAttack::Update()
{
	//プレイヤーがダメージを受けていない
	if (!GetPlayer().GetIsDamage()) {
		//手のボーンのワールド行列を取得
		CMatrix leftHandMatrix = m_enemy->GetBoneWorldMatrix(L"LeftHand");
		CVector3 leftHandPosition;
		leftHandPosition.x = leftHandMatrix.m[3][0];
		leftHandPosition.y = leftHandMatrix.m[3][1];
		leftHandPosition.z = leftHandMatrix.m[3][2];

		//プレイヤーとの距離を計算
		CVector3 playerPosition = GetPlayer().GetPosition();
		CVector3 distance = playerPosition - m_enemy->GetPosition();
		distance.y = 0.0f;
		length = distance.Length();
		{
			//敵の攻撃との距離を計算
			playerPosition.y += 2.5f;
			CVector3 distance = leftHandPosition - playerPosition;
			float length = distance.Length();
			if (length < 1.5f) {
				//プレイヤーがダメージを受けた
				GetPlayer().GetDamage();
			}
		}
	}

	if (m_enemy->IsDamage()) {
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了している
		if (!m_enemy->IsFind()) {
			//プレイヤーが視野内にいない
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		else if (m_enemy->IsFind() && length > 2.0f) {
			//プレイヤーが視野内にいる且つ距離が遠いなら近づく
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		else {
			//もう一度攻撃させる
			m_enemy->PlayAnimation(CEnemyState::enState_Attack);
		}
	}
}
