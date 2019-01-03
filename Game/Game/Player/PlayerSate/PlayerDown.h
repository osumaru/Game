#pragma once
#include "PlayerState.h"
class CPlayerDown : public IPlayerState
{
public:
	CPlayerDown();
	~CPlayerDown();
	void Init()override;

	void Update()override;

};

