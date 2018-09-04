#include "stdafx.h"
#include "Zombie.h"
#include "../GameCamera.h"
#include "../Itam/RecoveryItem.h"

void Zombie::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/zombi.cmo");
	m_position = position;
	m_characterController.Init(0.05f, 0.05f, m_position);
	m_characterController.SetGravity(-90.0f);
}

void Zombie::Update()
{
	//死亡時に回復アイテムとお金を出す
	//if (Pad().IsTriggerButton(enButtonA)) {
	//	CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
	//	recoveryItem->Init(m_position);
	//	Dead();
	//}

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisX, -90.0f);

	//m_characterController.SetPosition(m_position);
	//m_characterController.Execute(GetGameTime().GetDeltaFrameTime());
	//m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, rot, { 1.0f, 1.0f, 1.0f });
}

void Zombie::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
