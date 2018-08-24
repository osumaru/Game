#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"

void Player::Init(Vector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/U2.cmo");
	m_position = position;
	Add(this, 0);
}

void Player::Update()
{
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisX, -90.0f);
	m_skinmodel.Update(m_position, rot, { 1.0f, 1.0f, 1.0f });
}

void Player::Draw()
{
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}