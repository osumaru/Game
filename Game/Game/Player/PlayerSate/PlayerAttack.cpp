#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"


CPlayerAttack::CPlayerAttack()
{
}


CPlayerAttack::~CPlayerAttack()
{
}

bool CPlayerAttack::Start()
{

	GetPlayer().SetPlayerAnimation(GetPlayer().GetPlayerStateMachine().GetAttackSate(), 0.2f);
	return true;
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.3f)
	{
		GetPlayer().SetAttack(true);

	}
	//�U�����ɍU���̓��͂����ꂽ�ꍇ�͘A���Ɉڍs����
	if (Pad().IsTriggerButton(enButtonX) && !m_rock)
	{
		m_conAtaack = true;
		m_rock = true;
		GetPlayer().GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack2);
	}

	//�U���A�j���[�V�������I��������̏���
	if (!GetPlayer().GetAnimetion().IsPlay())
	{
		//�U�����[�V�������̓_���[�W���[�V�����������Ȃ�
		if (m_conAtaack)
		{
			Start();
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			m_conAtaack = false;
			m_animetionFrame = 0.0f;
		}
		else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
		{
			//����A�j���[�V����
			GetPlayer().GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			m_rock = false;
			m_animetionFrame = 0.0f;
		}

		else
		{
			GetPlayer().GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			m_rock = false;
			m_animetionFrame = 0.0f;

		}
	}
}
