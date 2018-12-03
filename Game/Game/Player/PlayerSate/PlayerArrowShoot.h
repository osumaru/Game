#pragma once
#include "PlayerState.h"
//�|��
class CPlayerArrowShoot : public IPlayerState
{
public:
	CPlayerArrowShoot();
	~CPlayerArrowShoot();
	void Init();
	void Update();
	bool IsShoot()
	{
		return m_isShoot;
	}
private:
	bool	m_isShoot = false;
};

