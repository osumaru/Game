#pragma once
#include "../INpcState.h"
#include "../../Item/CEquipItem.h"
class CWeaponShop : public INpcState
{
public:
	CWeaponShop();
	~CWeaponShop();
	void Init(const CVector3 position, const CQuaternion rotation);
	void Update();
	void Draw();
	void AfterDraw();
	void LineupChange();
private:
	CEquipItem			m_equipItem;
	float				m_changeUpTime = 0.0f;
};

