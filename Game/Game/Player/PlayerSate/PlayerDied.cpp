#include "stdafx.h"
#include "../Player.h"
#include "PlayerDied.h"


void CPlayerDied::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDete, 0.2f);
}

void CPlayerDied::Update()
{
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_pPlayerGetter->SetIsDied(true);

	}

}
