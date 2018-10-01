#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"


CPlayerAvoidance::CPlayerAvoidance()
{
}


CPlayerAvoidance::~CPlayerAvoidance()
{
}

bool CPlayerAvoidance::Start()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerAvoidance, 0.2f);
	return true;
}

void CPlayerAvoidance::Update()
{
	if (!GetPlayer().GetAnimetion().IsPlay())
	{

		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);

	}

}
