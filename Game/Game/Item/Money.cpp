#include "stdafx.h"
#include "Money.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"

void CMoney::Init()
{
}

bool CMoney::Start()
{
	//�����_���Ɉړ��������
	float randomPositionX = (float)Random().GetRandDouble();
	float randomPositionZ = (float)Random().GetRandDouble();
	//0.0�`6.0�̒l�ɕϊ�
	randomPositionX *= 6.0f;
	randomPositionZ *= 6.0f;
	//-3.0�`3.0�̒l�ɕϊ�
	randomPositionX -= 3.0f;
	randomPositionZ -= 3.0f;
	//�ړ���̃x�N�g�����v�Z
	CVector3 toRandomPosition;
	toRandomPosition.x = randomPositionX;
	toRandomPosition.y = 0.0f;
	toRandomPosition.z = randomPositionZ;

	//�ړ����x���v�Z
	toRandomPosition.Normalize();
	toRandomPosition *= m_speed;
	toRandomPosition.y = m_speed * 1.5f;
	m_characterController.SetMoveSpeed(toRandomPosition);

	return true;
}

void CMoney::Update()
{
	if (GetPlayer().GetIsDied() || m_timer > m_itemDeadTime)
	{
		//�v���C���[�����S�������͈�莞�Ԃō폜
		Delete(this);
		return;
	}

	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();

	//�n�ʂɐڒn������~�߂�
	if (!m_popEnd && m_characterController.IsOnGround()) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		m_popEnd = true;
	}

	//�L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
	m_characterController.SetMoveSpeed(moveSpeed);

	m_timer += GameTime().GetDeltaFrameTime();
	//�v���C���[�Ƃ̋������v�Z
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	float length = toPlayer.Length();
	if (m_popEnd && length < 5.0f) {
		m_moveSpeed = m_characterController.GetMoveSpeed();
		CVector3 toPlayerNormalize = toPlayer;
		toPlayerNormalize.Normalize();
		m_moveSpeed += toPlayerNormalize * m_timer;
		m_characterController.SetMoveSpeed(m_moveSpeed);
		if (length < 2.0f) {
			//�߂���Ίl��
			GetPlayer().GainGold(m_gold);
			Delete(this);
		}
	}

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);

}

void CMoney::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CMoney::Pop(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/money.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
	m_characterController.SetUserIndex(EnCollisionAttr::enCollisionAttr_Item);
}
