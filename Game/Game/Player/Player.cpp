#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"

void Player::Init(Vector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/U2.cmo");
	m_position = position;
	m_characterController.Init(2.0f, 2.0f, m_position);
	m_characterController.SetGravity(0.0f);
	Add(this, 0);
}

void Player::Update()
{
	Quaternion rot;
	Move();
	rot.SetRotationDeg(Vector3::AxisX, -90.0f);
	m_skinmodel.Update(m_position, rot, { 1.0f, 1.0f, 1.0f });
}

void Player::Draw()
{
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void Player::Move()
{
	m_moveSpeed.z = 2.0f * GetGameTime().GetDeltaFrameTime();
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GetGameTime().GetDeltaFrameTime());

	m_position = m_characterController.GetPosition();



}