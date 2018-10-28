#pragma once
#include "PlayerState.h"
class CPlayerJump: public IPlayerState
{
public:
	void Init()override;

	void Update()override;
};

