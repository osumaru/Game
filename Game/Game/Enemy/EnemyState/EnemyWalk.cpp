#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"

bool CEnemyWalk::Start()
{
	//歩きアニメーションを再生
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Walk, 0.3f);

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
	m_destination = m_enemy->GetEnemyGroup()->GetPosition() + toRandomPosition;

	m_isMoveEnd = false;
	return true;
}

void CEnemyWalk::Update()
{
	//移動
	Move();

	if (m_enemy->GetIsDamage()) {
		//ダメージを受けた
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (m_isMoveEnd) {
		//移動先まで移動したら止まる
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
	if (m_enemy->IsFind()) {
		//プレイヤーが視野内にいる
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}

void CEnemyWalk::Move()
{
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	float speed = 2.0f;

	CVector3 position = m_enemy->GetPosition();
	CVector3 distance = m_destination - position;
	distance.y = 0.0f;
	if (distance.Length() > 0.3f)
	{
		//移動先に移動する
		distance.Normalize();
		distance *= speed;
		moveSpeed.x = distance.x;
		moveSpeed.z = distance.z;
	}
	else
	{
		//移動先に着いた
		m_isMoveEnd = true;
	}

	m_enemy->SetMoveSpeed(moveSpeed);
}
