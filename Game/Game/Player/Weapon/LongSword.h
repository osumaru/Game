#pragma once
#include "IWeapon.h"

class CLongSword : public IWeapon
{
public:
	void Init()override;

	SWeaponEnemyAttackInfo EnemyAttackPositionDecide()override;

	SWeaponTraceDrawInfo WeaponTraceDraw()override;
};