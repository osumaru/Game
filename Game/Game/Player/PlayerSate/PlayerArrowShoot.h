#pragma once
#include "IPlayerState.h"
class CPlayerArrowShoot : public IPlayerState
{
public:
	CPlayerArrowShoot();
	~CPlayerArrowShoot();
	bool Start();
	void Update();
private:
	bool	m_isShoot = false;
};

