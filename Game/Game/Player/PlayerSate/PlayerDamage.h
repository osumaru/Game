#pragma once
#include "IPlayerState.h"
class CPlayerDamage : public IPlayerSate
{
public:
	CPlayerDamage();
	~CPlayerDamage();
	bool Start();
	void Update();
};

