#pragma once
#include "ItemShop.h"
#include "../../Item/GameItem/CEquipItem.h"
class CWeaponShop : public IShop
{
public:
	CWeaponShop();
	~CWeaponShop();
	void Init(const CVector3 position, const CQuaternion rotation, EShop shopType);
	void Update();
	void Draw();
	void PostAfterDraw();
	void LineupChange();
private:
	CEquipItem*			m_equipItem;
	float				m_changeUpTime = 0.0f;
	const int			DEFAULT_WEAPON[5] = { 0,1,2,10,11 };
	const int			PICUP_WEAPON[5] = { 5,6,12,13,14 };
};

