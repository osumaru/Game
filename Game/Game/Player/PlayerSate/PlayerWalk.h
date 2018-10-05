#pragma once
#include "IPlayerState.h"

class CPlayerWalk : public IPlayerState
{
public:
	CPlayerWalk();
	~CPlayerWalk();
	bool Start();
	void Update();

private:
};

