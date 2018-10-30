#include "stdafx.h"
#include "PlayerArrowShoot.h"
#include "../Player.h"


CPlayerArrowShoot::CPlayerArrowShoot()
{
}


CPlayerArrowShoot::~CPlayerArrowShoot()
{
}

void CPlayerArrowShoot::Init()
{
	//‹|‚ð‘Å‚Âƒ‚[ƒVƒ‡ƒ“
	m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerArrowShoot, 0.5f);
	m_pPlayer->SetAttack(true);
	m_isShoot = false;
}

void CPlayerArrowShoot::Update()
{
	if (Pad().GetRightTrigger())
	{
		m_isShoot = true;
	}


	if (!GetPlayer().GetAnimation().IsPlay())
	{
		//˜AŽËŽž‚Ìˆ—
		if (m_isShoot)
		{
			GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStand);
			m_pPlayer->SetAttack(false);

		}
	}


}
