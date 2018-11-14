#include "PlayerStun.h"
#include "../Player.h"

void CPlayerStun::Init()
{
	m_timer = 0.0f;
	m_pPlayerGetter->SetIsInvincible(true);
}

void CPlayerStun::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();
	if (1.0f < m_timer)
	{
		m_pPlayerGetter->DamageStateReset();
		m_pPlayerGetter->SetIsInvincible(false);
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}

}

