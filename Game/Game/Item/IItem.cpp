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
	if (distance <= 0.0f) {
		//その場にポップさせる
		m_moveSpeed = CVector3::Zero;
		m_moveSpeed.y = upSpeed;
		m_characterController.SetMoveSpeed(m_moveSpeed);
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
	m_moveSpeed.x = randomPositionX;
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = randomPositionZ;

	//移動速度を計算
	m_moveSpeed.Normalize();
	m_moveSpeed *= m_speed;
	m_moveSpeed.y = upSpeed;
	m_characterController.SetMoveSpeed(m_moveSpeed);
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
