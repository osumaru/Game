#pragma once
#include "IPlayerState.h"
class CPlayerJump: public IPlayerSate
{
public:
	CPlayerJump();
	~CPlayerJump();
	bool Start();

	void Update();
};

