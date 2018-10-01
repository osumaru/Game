#pragma once
#include "IPlayerState.h"
class CPlayerAvoidance: public IPlayerSate
{
public:
	CPlayerAvoidance();
	~CPlayerAvoidance();
	bool Start();
	void Update();
};

