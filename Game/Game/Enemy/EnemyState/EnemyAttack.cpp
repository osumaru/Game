#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//攻撃アニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Attack);

	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 speed = CVector3::Zero;
	moveSpeed.x = speed.x;
	moveSpeed.z = speed.z;
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
		{
			//敵の攻撃との距離を計算
			playerPosition.y += 2.5f;
			CVector3 distance = leftHandPosition - playerPosition;
			float length = distance.Length();
			if (length < 1.5f) {
				//プレイヤーがダメージを受けた
				GetPlayer().SetDamage(m_enemy->GetStatus().strength);
				GetPlayer().SetDamageEnemyPos(m_enemy->GetPosition());
			}
		}
	}

	//プレイヤーとの距離を計算
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 distance = playerPos - m_enemy->GetPosition();
	distance.y = 0.0f;
	float length = distance.Length();
	//扇状の範囲に入っているか
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (m_enemy->IsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	else if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了している
		if (!m_enemy->IsFind()) {
			//プレイヤーが視野内にいない
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		else if (isRange && length < 1.2f) {
			//攻撃範囲にはいっている
			m_timer += GameTime().GetDeltaFrameTime();
			if (m_timer > 3.0f) {
				m_timer = 0.0f;
				m_enemy->PlayAnimation(CEnemyState::enState_Attack);
			}
		}
		else {
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
	}
}
