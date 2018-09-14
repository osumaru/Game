#include "stdafx.h"
#include "PlayerState.h"


CPlayerState::CPlayerState()
{
}


CPlayerState::~CPlayerState()
{
}


void CPlayerState::Init()
{

	m_state = enPlayerStand;
}

void CPlayerState::Update()
{

	switch (m_state)
	{
	case enPlayerStand:

		m_playerStand.Update();
		break;

	case enPlayerWalk:

		break;
	default:
		break;
	}

}
