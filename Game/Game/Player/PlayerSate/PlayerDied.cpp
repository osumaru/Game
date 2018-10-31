#include "stdafx.h"
#include "../Player.h"
#include "PlayerDied.h"


void CPlayerDied::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationDete, 0.2f);
}

void CPlayerDied::Update()
{
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		m_pPlayer->SetIsDeid(true);

	}

}
