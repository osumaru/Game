#pragma once
#include "IPlayerState.h"
class CPlayerArrowAttack : public IPlayerState
{
public:
	CPlayerArrowAttack();
	~CPlayerArrowAttack();
	bool Start();
	void Update();
	const bool IsCharge()
	{
		return	m_isCharge;
	}
private:
	float					m_animetionFrame = 0.0f;
	bool					m_isCharge = false;			//ƒ`ƒƒ[ƒW’†‚©‚Ì”»’è

};

