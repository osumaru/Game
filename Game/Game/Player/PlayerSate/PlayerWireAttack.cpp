#include "PlayerWireAttack.h"
#include "../Player.h"
#include "../../Command/Command.h"

void CPlayerWireAttack::Init()
{
	IPlayerState::Init();
	m_isStateTransition = true;
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireAttack, 0.2f);
}

void CPlayerWireAttack::Update()
{
	bool isAnimationPlay = m_pPlayerGetter->GetAnimation().IsPlay();

	if (!isAnimationPlay) {
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}
