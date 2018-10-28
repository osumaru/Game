#pragma once
#include "PlayerState.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"

class CPlayerStand : public IPlayerState
{
public:
	void Init()override;

	void Update()override;

	void ChangeWepon();
private:
	
};

