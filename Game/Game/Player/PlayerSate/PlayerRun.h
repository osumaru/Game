#pragma once
#include"IPlayerState.h"

class CPlayerRun	: public	IPlayerState
{
public:
	CPlayerRun();
	~CPlayerRun();
	bool Start();
	void Update();

private:

};

