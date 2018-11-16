#pragma once
#include "IWeapon.h"

class CSword : public IWeapon
{
public:

	void Init()override;

	void EnemyAttack()override;
	
private:

};