#include "stdafx.h"
#include "Money.h"
#include "../Player/Player.h"
#include "../GameCamera.h"

void CMoney::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/money.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
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
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	moveSpeed.x = toRandomPosition.x;
	moveSpeed.y = 6.0f;
	moveSpeed.z = toRandomPosition.z;
	m_characterController.SetMoveSpeed(moveSpeed);

	return true;
}

void CMoney::Update()
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

void CMoney::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CMoney::Move()
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
