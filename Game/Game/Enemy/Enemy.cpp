#include "stdafx.h"
#include "Enemy.h"
#include "../GameCamera.h"

void Enemy::Init(Vector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/testBox.cmo");
	m_position = position;
	Add(this, 0);
}

void Enemy::Update()
{
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisX, -90.0f);
	m_skinmodel.Update(m_position, rot, { 1.0f, 1.0f, 1.0f });
}

void Enemy::Draw()
{
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
