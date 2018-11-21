#pragma once
#include "ItemShop.h"
#include "../../Item/CEquipItem.h"
class CWeaponShop : public IShop
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
	const int			DEFAULT_WEAPON[5] = { 0,1,2,3,4 };
	const int			PICUP_WEAPON[5] = { 5,6,7,8,9 };
};

