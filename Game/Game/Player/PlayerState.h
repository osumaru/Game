#pragma once
#include "Player.h"
#include "PlayerStand.h"

class CPlayerState
{
public:
	CPlayerState();
	~CPlayerState();
	void Init();
	void Update();
	enum EnPlayerState
	{
		enPlayerStand,
		enPlayerWalk,
		enPlayerRun,
		enPlayerJump,
		enPlayerAttack,
		enPlayerDamage,
		enPlayerAvoidance,
		enPlayerDete,
		enPlayerArroAttack,
		enPlayerNum

	};
private:
	EnPlayerState	m_state;
	CPlayerStand	m_playerStand;
	
};

