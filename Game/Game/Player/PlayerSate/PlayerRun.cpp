#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"



CPlayerRun::CPlayerRun()
{
}


CPlayerRun::~CPlayerRun()
{
}
bool CPlayerRun::Start()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerRun, 0.2f);
	return true;
}

void CPlayerRun::Update()
{

	if (GetPlayer().GetIsDamage()       )
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}

	else if (Pad().IsTriggerButton(enButtonX))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAttack);
	}

	else if (fabs(GetPlayer().GetMoveSpeed().Length()) == 0.0f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}
}