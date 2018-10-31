#pragma once
#include "PlayerState.h"
//‹|‚ð
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

