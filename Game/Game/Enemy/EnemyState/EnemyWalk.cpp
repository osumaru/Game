#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"

bool EnemyWalk::Start()
{
	//歩きアニメーションを再生
	m_enemy->PlayAnimation(CEnemyState::enState_Walk);

	//ランダムに移動先を決定
	float randomPositionX = (float)Random().GetRandDouble();
	float randomPositionZ = (float)Random().GetRandDouble();
	//0.0～20.0の値に変換
	randomPositionX *= 20.0f;
	randomPositionZ *= 20.0f;
	//-10.0～10.0の値に変換
	randomPositionX -= 10.0f;
	randomPositionZ -= 10.0f;
	//移動先のベクトルを計算
	CVector3 toRandomPosition;
	toRandomPosition.x = randomPositionX;
	toRandomPosition.y = 0.0f;
	toRandomPosition.z = randomPositionZ;

	//移動先の座標を保存
	m_destination = m_enemy->GetInitPosition() + toRandomPosition;

	//移動速度を計算
	toRandomPosition.Normalize();
	toRandomPosition *= m_speed;
	m_enemy->SetMoveSpeed(toRandomPosition);

	return true;
}

void EnemyWalk::Update()
{
	bool isMoveFinish = false;
	//移動速度を取得
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	//現在の座標から移動先までの距離を計算
	CVector3 position = m_enemy->GetPosition();
	CVector3 distance = m_destination - position;
	float length = distance.Length();
	if (length > 0.3f) {
		//近くなければそのまま進む
		distance.Normalize();
		distance *= m_speed;
		moveSpeed.x = distance.x;
		moveSpeed.z = distance.z;
	}
	else {
		isMoveFinish = true;
	}
	//移動速度を設定
	m_enemy->SetMoveSpeed(moveSpeed);

	//移動先まで移動したら止まる
	if (isMoveFinish) {
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
}
