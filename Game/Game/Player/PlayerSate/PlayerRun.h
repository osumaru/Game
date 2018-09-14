#pragma once
#include"IPlayerState.h"

class CPlayerRun	: public	IPlayerSate
{
public:
	CPlayerRun();
	~CPlayerRun();
	bool Start();
	void Update();

private:

};

