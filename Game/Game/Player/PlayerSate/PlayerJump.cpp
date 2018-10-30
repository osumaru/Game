#include "stdafx.h"
#include "PlayerJump.h"
#include "../Player.h"


void CPlayerJump::Init()
{
	CVector3 moveSpeed = m_pPlayer->GetMoveSpeed();
	moveSpeed.y += 10.0f;
	m_pPlayer->SetMoveSpeed(moveSpeed);
	if (m_pPlayer->GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerRunJump)
	{
		m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerRunJump, 0.0f);
	}
	else
	{
		m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerJump, 0.2f);
	}
}

void CPlayerJump::Update()
{


	if (/*!GetPlayer().GetAnimation().IsPlay() || */m_pPlayer->GetCharacterController().IsOnGround())
	{
		if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerRun);
		}
		else
		{

			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStand);

		}

	}
}
