#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//移動しない
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);

	//攻撃アニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enAnimation_Attack);

	m_enemy->Attack();

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

	if (m_enemy->IsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->IsPlayAnimation()) {
		//アニメーションが終了している
		m_esm->ChangeState(CEnemyState::enState_AttackWait);
	}
}