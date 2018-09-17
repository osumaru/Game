#pragma once
#include"IPlayerState.h"
class CPlayerAttack : public  IPlayerSate
{
public:
	CPlayerAttack();
	~CPlayerAttack();
	bool Start();
	void Update();
private:
	float					m_animetionFrame = 0.0f;

};

