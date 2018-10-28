#pragma once
#include"PlayerState.h"

class CPlayerRun	: public	IPlayerState
{
public:
	void Init()override;

	void Update()override;
};

