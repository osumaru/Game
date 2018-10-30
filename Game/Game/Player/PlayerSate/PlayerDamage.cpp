#include "stdafx.h"
#include "PlayerDamage.h"
#include "../Player.h"



void CPlayerDamage::Init()
{
	m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerDamage, 0.2f);
}

void CPlayerDamage::Update()
{
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStand);
		m_pPlayer->SetIsDamage(false);
		m_pPlayer->SetInterval(true);			//–³“GŽžŠÔ‚ð“K‰ž‚³‚¹‚é

	}
}