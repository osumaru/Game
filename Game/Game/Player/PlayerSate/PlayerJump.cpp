#include "stdafx.h"
#include "PlayerJump.h"
#include "../Player.h"


CPlayerJump::CPlayerJump()
{
}


CPlayerJump::~CPlayerJump()
{
}

bool CPlayerJump::Start()
{
	if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerRunJump)
	{
		GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerRunJump, 0.0f);
	}
	else
	{

		GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerJump, 0.2f);
	}
	return true;
}

void CPlayerJump::Update()
{


	if (!GetPlayer().GetAnimation().IsPlay() || GetPlayer().GetIsGround())
	{
		if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
		{
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
		}
		else
		{

			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);

		}

	}
}
