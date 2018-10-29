#pragma once
#include "PlayerState.h"
class CPlayerArrowShoot : public IPlayerState
{
public:
	CPlayerArrowShoot();
	~CPlayerArrowShoot();
	void Init();
	void Update();
private:
	bool	m_isShoot = false;
};

