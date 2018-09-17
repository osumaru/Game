#pragma once
#include "IPlayerState.h"
class CPlayerDied : public IPlayerSate
{
public:
	CPlayerDied();
	~CPlayerDied();
	bool Start();
	void Update();
};

