#pragma once
#include "IPlayerState.h"

class CPlayerStand	:	public IPlayerSate
{
public:
	CPlayerStand();
	~CPlayerStand();
	bool Start();
	void Update();
};

