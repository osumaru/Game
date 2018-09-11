#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool EnemyAttack::Start()
{
	//攻撃アニメーションを再生
	m_enemy->PlayAnimation(EnemyState::enState_Attack);
	return true;
}

void EnemyAttack::Update()
{
	//手のボーンのワールド行列を取得
	CMatrix leftHandMatrix = m_enemy->GetBoneWorldMatrix(L"LeftHand");
	CVector3 leftHandPosition;
	leftHandPosition.x = leftHandMatrix.m[3][0];
	leftHandPosition.y = leftHandMatrix.m[3][1];
	leftHandPosition.z = leftHandMatrix.m[3][2];

	//プレイヤーとの距離を計算
	CVector3 playerPosition = GetPlayer().GetPosition();
	playerPosition.y += 2.5f;
	CVector3 distance = leftHandPosition - playerPosition;
	float length = distance.Length();
	if (length < 1.5f) {
		//ダメージを受けた
		GetPlayer().GetDamage();
		m_enemy->SetIsAttackHit(true);
	}

	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(EnemyState::enState_Damage);
		m_enemy->SetIsAttackHit(false);
	}
}
