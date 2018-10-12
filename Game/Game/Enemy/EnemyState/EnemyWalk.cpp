#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"

bool CEnemyWalk::Start()
{
	//歩きアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Walk);

	//ランダムに移動先を決定
	float randomPositionX = (float)Random().GetRandDouble();
	float randomPositionZ = (float)Random().GetRandDouble();
	//0.0〜20.0の値に変換
	randomPositionX *= 20.0f;
	randomPositionZ *= 20.0f;
	//-10.0〜10.0の値に変換
	randomPositionX -= 10.0f;
	randomPositionZ -= 10.0f;
	//移動先のベクトルを計算
	CVector3 toRandomPosition;
	toRandomPosition.x = randomPositionX;
	toRandomPosition.y = 0.0f;
	toRandomPosition.z = randomPositionZ;

	//移動先の座標を保存
	m_destination = m_enemyGroup->GetPosition() + toRandomPosition;

	//移動速度を計算
	toRandomPosition.Normalize();
	toRandomPosition *= m_speed;
	m_enemy->SetMoveSpeed(toRandomPosition);

	return true;
}

void CEnemyWalk::Update()
{
	bool isMoveEnd = false;
	//移動速度を取得
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	//現在の座標から移動先までの距離を計算
	CVector3 position = m_enemy->GetPosition();
	CVector3 distance = m_destination - position;
	distance.y = 0.0f;
	float length = distance.Length();
	if (length > 0.3f) {
		//近くなければそのまま進む
		distance.Normalize();
		distance *= m_speed;
		moveSpeed.x = distance.x;
		moveSpeed.z = distance.z;
	}
	else {
		isMoveEnd = true;
	}
	//移動速度を設定
	m_enemy->SetMoveSpeed(moveSpeed);

	if (m_enemy->IsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (isMoveEnd) {
		//移動先まで移動したら止まる
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
	if (m_enemy->IsFind()) {
		//プレイヤーが視野内にいる
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}
