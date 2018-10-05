#pragma once
#include "IPlayerState.h"
class CPlayerDied : public IPlayerState
{
public:
	CPlayerDied();
	~CPlayerDied();
	bool Start();
	void Update();
};

