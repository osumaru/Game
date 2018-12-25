#pragma once
#include "PlayerState.h"
class CPlayerSky :
	public IPlayerState
{
public:
	CPlayerSky();

	void Init() override;

	void Update() override;

};

