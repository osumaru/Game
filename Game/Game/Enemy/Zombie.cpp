#include "stdafx.h"
#include "Zombie.h"
#include "../GameCamera.h"
#include "../Itam/RecoveryItem.h"
#include "../Itam/Money.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/zombi.cmo", &m_animation);
	m_position = position;
	m_rotation.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-90.0f);
	wchar_t* animClip[5] = { 
		L"Assets/modelData/zombiStand.tka",
		L"Assets/modelData/zombiWalk.tka",
		L"Assets/modelData/zombiAttack.tka",
		L"Assets/modelData/zombiDamage.tka",
		L"Assets/modelData/zombiDeath.tka"
	};
	m_animation.Init(animClip, 5);
	m_animation.SetLoopFlg(0, true);
	m_animation.SetLoopFlg(1, true);
	m_animation.SetLoopFlg(2, true);
	Add(&m_enemyStateMachine, 0);
}

void Zombie::Update()
{
	//���S���ɉ񕜃A�C�e���Ƃ������o��
	if (Pad().IsTriggerButton(enButtonA)) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(0);
		CMoney* money = New<CMoney>(0);
		CVector3 itemPosition = m_position;
		itemPosition.y += 0.5f;
		recoveryItem->Init(itemPosition);
		money->Init(itemPosition);
		m_enemyStateMachine.Release();
		Delete(this);
	}

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	//�A�j���[�V�����̔ԍ����ς���Ă�����Đ�
	if (m_animNum != m_animNumOld) {
		m_animation.Play(m_animNum, 1.0f);
	}
	m_animNumOld = m_animNum;

	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void Zombie::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
