#pragma once
#include "IPlayerState.h"
class CPlayerAvoidance: public IPlayerState
{
public:
	CPlayerAvoidance();
	~CPlayerAvoidance();
	bool Start();
	void Update();
};

