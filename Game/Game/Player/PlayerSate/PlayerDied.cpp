#include "stdafx.h"
#include "../Player.h"
#include "PlayerDied.h"


CPlayerDied::CPlayerDied()
{
}


CPlayerDied::~CPlayerDied()
{
}

bool CPlayerDied::Start()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerDied, 0.2f);
	return true;
}

void CPlayerDied::Update()
{

	if (!GetPlayer().GetAnimation().IsPlay())
	{
		GetPlayer().SetIsDeid(true);

	}

}
