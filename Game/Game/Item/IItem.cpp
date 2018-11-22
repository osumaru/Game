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
		//���̏�Ƀ|�b�v������
		m_moveSpeed = CVector3::Zero;
		m_moveSpeed.y = upSpeed;
		m_characterController.SetMoveSpeed(m_moveSpeed);
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
	m_moveSpeed.x = randomPositionX;
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = randomPositionZ;

	//�ړ����x���v�Z
	m_moveSpeed.Normalize();
	m_moveSpeed *= m_speed;
	m_moveSpeed.y = upSpeed;
	m_characterController.SetMoveSpeed(m_moveSpeed);
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
