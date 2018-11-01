#include "stdafx.h"
#include "PlayerDamage.h"
#include "../Player.h"



void CPlayerDamage::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationDamage, 0.2f);
}

void CPlayerDamage::Update()
{
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
		m_pPlayer->SetIsDamage(false);
		m_pPlayer->SetInterval(true);			//無敵時間を適応させる

	}
}