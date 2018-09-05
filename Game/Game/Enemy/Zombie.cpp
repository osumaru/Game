#include "stdafx.h"
#include "Zombie.h"
#include "../GameCamera.h"
#include "../Itam/RecoveryItem.h"

Zombie::Zombie():
	m_enemyStateMachine(this)
{
}

Zombie::~Zombie()
{
}

void Zombie::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/zombi.cmo", &m_animation);
	m_position = position;
	m_characterController.Init(0.7f, 0.7f, m_position);
	m_characterController.SetGravity(-90.0f);
	wchar_t* animClip[1] = { L"Assets/modelData/zombiStand.tka" };
	m_animation.Init(animClip, 1);
	Add(&m_enemyStateMachine, 0);
}

void Zombie::Update()
{
	//死亡時に回復アイテムとお金を出す
	//if (Pad().IsTriggerButton(enButtonA)) {
	//	CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
	//	recoveryItem->Init(m_position);
	//	m_enemyStateMachine.Release();
	//	Dead();
	//}

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisX, -90.0f);

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	if (Pad().IsTriggerButton(enButtonA)) {
		m_animation.Play(0);
	}
	m_animation.Update(GameTime().GetDeltaFrameTime());

	m_skinModel.Update(m_position, rot, { 1.0f, 1.0f, 1.0f });
}

void Zombie::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
