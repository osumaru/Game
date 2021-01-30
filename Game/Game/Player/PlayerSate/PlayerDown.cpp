#include "stdafx.h"
#include "PlayerDown.h"
#include "PlayerState.h"
#include "../Player.h"
#include "../../Command/Command.h"

CPlayerDown::CPlayerDown()
{
}


CPlayerDown::~CPlayerDown()
{
}

void CPlayerDown::Init()
{
	IPlayerState::Init();
	m_isStateTransition = true;
	const float RollVolume = 0.3f;
	/*CSoundSource* RollSound = New<CSoundSource>(0);
	RollSound->Init("Assets/sound/Battle/Roll.wav");
	RollSound->Play(false);
	RollSound->SetVolume(RollVolume);*/
	//アニメーションの再生
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDown, 0.2f);
}

void CPlayerDown::Update()
{
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	if (!m_pPlayerGetter->GetAnimation().IsPlay()&& m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationUp
		&& m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStand))
	{
		m_pPlayer->SetCommand(new StandCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
	{
		m_pPlayer->SetCommand(new RunCommand(m_pPlayer));
	}
	else if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationUp, 0.2f);
	}
}
