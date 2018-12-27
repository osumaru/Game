#include "stdafx.h"
#include "IItem.h"
#include "../Player/Player.h"

IItem::IItem()
{
}

IItem::~IItem()
{
}

void IItem::RamdomPop(float distance, float upSpeed)
{
	CVector3 moveSpeed = CVector3::Zero;
	if (distance <= 0.0f) {
		//その場にポップさせる
		moveSpeed.y = upSpeed;
		m_characterController.SetMoveSpeed(moveSpeed);
		return;
	}
	//ランダムに移動先を決定
	float randomPositionX = (float)Random().GetRandDouble();
	float randomPositionZ = (float)Random().GetRandDouble();
	//ランダム地点までの距離に変換
	randomPositionX *= distance * 2.0f;
	randomPositionZ *= distance * 2.0f;
	randomPositionX -= distance;
	randomPositionZ -= distance;
	//移動先のベクトルを計算
	moveSpeed.x = randomPositionX;
	moveSpeed.y = 0.0f;
	moveSpeed.z = randomPositionZ;

	//移動速度を計算
	float speed = 4.0f;
	moveSpeed.Normalize();
	moveSpeed *= speed;
	moveSpeed.y = upSpeed;
	m_characterController.SetMoveSpeed(moveSpeed);
}

bool IItem::PickUp(bool isPopEnd, float length)
{
	if (!isPopEnd) {
		//ポップし終わっていないから何もしない
		return false;
	}
	//プレイヤーとの距離を計算
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	float playerLength = toPlayer.Length();
	if (playerLength < length) {
		return true;
	}
	return false;
}

CVector3 IItem::Move()
{
	float speed = 4.0f;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayer = playerPos - m_position;
	toPlayer.Normalize();
	toPlayer *= speed + m_accele;
	m_accele += 0.3f;
	return toPlayer;
}
