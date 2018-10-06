#pragma once
#include "IPlayerState.h"
class CPlayerJump: public IPlayerState
{
public:
	CPlayerJump();
	~CPlayerJump();
	bool Start();

	void Update();
};

