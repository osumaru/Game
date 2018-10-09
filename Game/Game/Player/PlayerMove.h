#pragma once
#include "PlayerSate/IPlayerState.h"

class CPlayerMove : public IPlayerState
{
public:
	CPlayerMove();
	~CPlayerMove();
	bool Start();
	void Update();

private:
	const float				RUN_SPEED = 1.8f;
	const float				WALK_SPEED = 3.8f;
	CVector3				m_PlayerMoveSpeed;
};

