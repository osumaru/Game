#include "stdafx.h"
#include "PlayerDamage.h"
#include "../Player.h"



void CPlayerDamage::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDamage, 0.1f);
}

void CPlayerDamage::Update()
{
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_pPlayerGetter->DamageStateReset();
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}