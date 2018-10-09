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

	if (!GetPlayer().GetAnimation().IsPlay())
	{

		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
		GetPlayer().SetIsDamage(false);
		GetPlayer().SetInterval(true);			//���G���Ԃ�K��������

	}
}