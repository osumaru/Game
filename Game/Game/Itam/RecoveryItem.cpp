#include "stdafx.h"
#include "RecoveryItem.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Player/Player.h"

void CRecoveryItem::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/heart.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
}

bool CRecoveryItem::Start()
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
	toRandomPosition.y = 6.0f;
	m_characterController.SetMoveSpeed(toRandomPosition);

	return true;
}

void CRecoveryItem::Update()
{
	Move();

	//�v���C���[�Ƃ̋������v�Z
	CVector3 toPlayer = m_position - GetPlayer().GetPosition();
	float length = toPlayer.Length();
	if (length < 1.0f) {
		//�߂���Ίl��
		Delete(this);
	}

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CRecoveryItem::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CRecoveryItem::Move()
{
	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();

	//�n�ʂɐڒn������~�߂�
	if (m_characterController.IsOnGround()) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
	}

	//�L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
	m_characterController.SetMoveSpeed(moveSpeed);
}
