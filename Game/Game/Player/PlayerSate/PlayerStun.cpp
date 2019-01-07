#include "PlayerStun.h"
#include "../Player.h"

void CPlayerStun::Init()
{
	m_timer = 0.0f;
	m_pPlayerGetter->SetIsInvincible(true);
	//m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationStun);
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDown);
}

void CPlayerStun::Update()
{
	CAnimation& anim = m_pPlayerGetter->GetAnimation();
	if (anim.GetCurrentAnimationNum() == enPlayerAnimationDown)
	{
		if (!anim.IsPlay())
		{
			m_timer += GameTime().GetDeltaFrameTime();
			if (1.0f < m_timer)
			{
				anim.Play(enPlayerAnimationUp, 0.5f);
				m_timer = 0.0f;
			}
		}
	}
	else
	{
		m_timer += GameTime().GetDeltaFrameTime();
		if(1.7f < m_timer)
		{
			m_pPlayerGetter->StanDamageStateReset();
			m_pPlayerGetter->SetIsInvincible(false);
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
		}
	}

}

