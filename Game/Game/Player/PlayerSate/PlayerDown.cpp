#include "stdafx.h"
#include "PlayerDown.h"
#include "PlayerState.h"
#include "../Player.h"

CPlayerDown::CPlayerDown()
{
}


CPlayerDown::~CPlayerDown()
{
}

void CPlayerDown::Init()
{
	//アニメーションの再生
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDown, 0.2f);
}

void CPlayerDown::Update()
{
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	if (!m_pPlayerGetter->GetAnimation().IsPlay()&& m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationUp)
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
	else if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationUp, 0.2f);
	}
}
