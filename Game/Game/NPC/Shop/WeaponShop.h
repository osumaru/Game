#pragma once
#include "../INpcState.h"
class CWeaponShop : public INpcState
{
public:
	CWeaponShop();
	~CWeaponShop();
	void Init(const CVector3 position, const CQuaternion rotation);
	void Update();
	void Draw();
private:
};

