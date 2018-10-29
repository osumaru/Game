#include "stdafx.h"
#include "../Player.h"
#include "PlayerDied.h"


void CPlayerDied::Init()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerDied, 0.2f);
}

void CPlayerDied::Update()
{
	if (!GetPlayer().GetAnimation().IsPlay())
	{
		GetPlayer().SetIsDeid(true);

	}

}
