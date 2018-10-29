#pragma once
#include "PlayerSate/PlayerState.h"

class CPlayerMove
{
public:
	void Update();

	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	bool					m_isActive = true;
	const float				RUN_SPEED = 1.8f;
	const float				WALK_SPEED = 3.8f;
	CVector3				m_PlayerMoveSpeed;
};

