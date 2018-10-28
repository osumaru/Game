#pragma once
#include "PlayerState.h"
class CPlayerArrowAttack : public IPlayerState
{
public:

	void Init()override;

	void Update()override;

	const bool IsCharge()
	{
		return	m_isCharge;
	}
private:
	float					m_animetionFrame = 0.0f;
	bool					m_isCharge = false;			//ƒ`ƒƒ[ƒW’†‚©‚Ì”»’è

};

