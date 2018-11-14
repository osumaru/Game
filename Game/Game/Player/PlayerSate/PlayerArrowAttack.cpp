#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"


void CPlayerArrowAttack::Init()
{
	//‹|‚Ì¶¬
	m_pPlayer->InitArrow();
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowAttack, 0.5f);
	m_pPlayerGetter->SetIsAttack(true);
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	//‹|—p‚ÌŽ‹“_‚É•ÏX
}

void CPlayerArrowAttack::Update()
{
	if (Pad().IsPressButton(enButtonRightTrigger))
	{
		m_isCharge = true;
	}
	else
	{
		m_isCharge = false;
	}

	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{

		if (!m_isCharge)
		{

			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowShoot);
		}
		
	}

}
