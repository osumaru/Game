#pragma once
#include "IWeapon.h"

class CSword : public IWeapon
{
public:

	void Init()override;

	void Update()override;

	SWeaponEnemyAttackInfo EnemyAttackPositionDecide()override;

	SWeaponTraceDrawInfo WeaponTraceDraw()override;
};