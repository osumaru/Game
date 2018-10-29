#pragma once
#include "PlayerState.h"
class CPlayerDied : public IPlayerState
{
public:
	void Init()override;

	void Update()override;
};

