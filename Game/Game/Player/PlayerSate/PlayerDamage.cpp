#include "stdafx.h"
#include "PlayerDamage.h"
#include "../Player.h"



void CPlayerDamage::Init()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerDamage, 0.2f);
}

void CPlayerDamage::Update()
{
	if (!GetPlayer().GetAnimation().IsPlay())
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
		GetPlayer().SetIsDamage(false);
		GetPlayer().SetInterval(true);			//–³“GŽžŠÔ‚ð“K‰ž‚³‚¹‚é

	}
}