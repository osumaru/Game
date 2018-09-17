#include "stdafx.h"
#include "PlayerDamage.h"
#include "../Player.h"


CPlayerDamage::CPlayerDamage()
{
}


CPlayerDamage::~CPlayerDamage()
{
}

bool CPlayerDamage::Start()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerDamage, 0.2f);
	return true;
}

void CPlayerDamage::Update()
{

	if (!GetPlayer().GetAnimetion().IsPlay())
	{

		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
		GetPlayer().SetIsDamage(false);

	}
}