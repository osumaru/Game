#pragma once
#include "IWeapon.h"

class CSword : public IWeapon
{
public:

	void Init()override;

	void EnemyAttackPositionDecide()override;
	
private:

};