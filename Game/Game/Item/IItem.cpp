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
		//���̏�Ƀ|�b�v������
		moveSpeed.y = upSpeed;
		m_characterController.SetMoveSpeed(moveSpeed);
		return;
	}
	//�����_���Ɉړ��������
	float randomPositionX = (float)Random().GetRandDouble();
	float randomPositionZ = (float)Random().GetRandDouble();
	//�����_���n�_�܂ł̋����ɕϊ�
	randomPositionX *= distance * 2.0f;
	randomPositionZ *= distance * 2.0f;
	randomPositionX -= distance;
	randomPositionZ -= distance;
	//�ړ���̃x�N�g�����v�Z
	moveSpeed.x = randomPositionX;
	moveSpeed.y = 0.0f;
	moveSpeed.z = randomPositionZ;

	//�ړ����x���v�Z
	float speed = 4.0f;
	moveSpeed.Normalize();
	moveSpeed *= speed;
	moveSpeed.y = upSpeed;
	m_characterController.SetMoveSpeed(moveSpeed);
}

bool IItem::PickUp(bool isPopEnd, float length)
{
	if (!isPopEnd) {
		//�|�b�v���I����Ă��Ȃ����牽�����Ȃ�
		return false;
	}
	//�v���C���[�Ƃ̋������v�Z
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
