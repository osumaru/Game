#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"



void CPlayerAttack::Init()
{
	m_pPlayer->SetPlayerAnimation(m_pPlayer->GetPlayerStateMachine().GetState(), 0.2f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.3f)
	{
		m_pPlayer->SetAttack(true);

	}
	//�U�����ɍU���̓��͂����ꂽ�ꍇ�͘A���Ɉڍs����
	if (Pad().IsTriggerButton(enButtonRightTrigger) && !m_rock)
	{
		m_conAtaack = true;
		m_rock = true;
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerAttack2);
	}

	//�U���A�j���[�V�������I��������̏���
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		//�U�����[�V�������̓_���[�W���[�V�����������Ȃ�
		if (m_conAtaack)
		{
			Init();
			m_conAtaack = false;
			m_animetionFrame = 0.0f;
		}
		else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
		{
			//����A�j���[�V����
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerAttack);
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerRun);
			m_pPlayer->SetAttack(false);
			m_rock = false;
			m_animetionFrame = 0.0f;
		}

		else
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerAttack);
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStand);
			m_pPlayer->SetAttack(false);
			m_rock = false;
			m_animetionFrame = 0.0f;

		}
	}
}
