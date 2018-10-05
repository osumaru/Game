#pragma once
#include "IPlayerState.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"

class CPlayerStand	:	public IPlayerState
{
public:
	CPlayerStand();
	~CPlayerStand();
	bool Start();
	void Update();
	void ChangeWepon();
private:
	
};

