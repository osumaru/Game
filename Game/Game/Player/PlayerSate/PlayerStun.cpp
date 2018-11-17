#include "PlayerStun.h"
#include "../Player.h"

void CPlayerStun::Init()
{
	m_timer = 0.0f;
	m_pPlayerGetter->SetIsInvincible(true);
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationStun);
}

void CPlayerStun::Update()
{
	CAnimation& anim = m_pPlayerGetter->GetAnimation();
	if (anim.GetCurrentAnimationNum() == enPlayerAnimationStun)
	{
		if (!anim.IsPlay())
		{
			m_timer += GameTime().GetDeltaFrameTime();
			if (1.0f < m_timer)
			{
				anim.Play(enPlayerAnimationStand, 0.5f);
				m_timer = 0.0f;
			}
		}
	}
	else
	{
		m_timer += GameTime().GetDeltaFrameTime();
		if(0.5f < m_timer)
		{
			m_pPlayerGetter->DamageStateReset();
			m_pPlayerGetter->SetIsInvincible(false);
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
		}
	}

}

