#pragma once
#include "PlayerState.h"
//プレイヤーが死んだときノステート

class CPlayerDied : public IPlayerState
{
public:
	void Init()override;

	void Update()override;
};

