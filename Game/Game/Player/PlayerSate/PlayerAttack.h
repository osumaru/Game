#pragma once
#include"IPlayerState.h"
class CPlayerAttack : public  IPlayerState
{
public:
	CPlayerAttack();
	~CPlayerAttack();
	bool Start();
	void Update();
private:
	float					m_animetionFrame = 0.0f;
	bool					m_conAtaack = false;
	bool					m_rock = false;			//˜AŒ‚‚ğI‚í‚ç‚·‚½‚ß‚Ì•Ï”

};

