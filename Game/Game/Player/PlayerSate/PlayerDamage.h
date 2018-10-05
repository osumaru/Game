#pragma once
#include "IPlayerState.h"
class CPlayerDamage : public IPlayerState
{
public:
	CPlayerDamage();
	~CPlayerDamage();
	bool Start();
	void Update();
};

