#pragma once
#include "IPlayerState.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"

class CPlayerStand	:	public IPlayerSate
{
public:
	CPlayerStand();
	~CPlayerStand();
	bool Start();
	void Update();
	void ChangeWepon();
private:
	
};

