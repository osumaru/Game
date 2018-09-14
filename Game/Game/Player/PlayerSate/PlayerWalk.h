#pragma once
#include "IPlayerState.h"

class CPlayerWalk : public IPlayerSate
{
public:
	CPlayerWalk();
	~CPlayerWalk();
	bool Start();
	void Update();

private:
};

