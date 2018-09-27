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
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerJump, 0.2f);
	return true;
}

void CPlayerJump::Update()
{

	if (!GetPlayer().GetAnimetion().IsPlay())
	{

		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);

	}
}
