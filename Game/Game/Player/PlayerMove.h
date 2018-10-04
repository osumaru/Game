#pragma once
#include "PlayerSate/IPlayerState.h"

class CPlayerMove : public IPlayerSate
{
public:
	CPlayerMove();
	~CPlayerMove();
	bool Start();
	void Update();

private:
	const float				RUN_SPEED = 2.4f;
	const float				WALK_SPEED = 2.8f;
	CVector3				m_PlayerMoveSpeed;
};

