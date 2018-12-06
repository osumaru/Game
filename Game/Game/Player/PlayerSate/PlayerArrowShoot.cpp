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
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowShoot, 0.5f);
	m_isShoot = false;
}

void CPlayerArrowShoot::Update()
{
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_isShoot = true;
	}


	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//˜AŽËŽž‚Ìˆ—
		if (m_isShoot)
		{
			GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
		}
		else
		{
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
			m_pPlayer->GetWeaponManager().SetIsAttack(false);

		}
	}


}
