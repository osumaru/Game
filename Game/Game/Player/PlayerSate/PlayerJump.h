#pragma once
#include "PlayerState.h"
//プレイヤーがジャンプするときのステート
class CPlayerJump: public IPlayerState
{
public:
	void Init()override;

	void Update()override;
};

