#pragma once
//武器の種類の列挙型
enum EnPlayerWeapon
{
	enWeaponSword,			//片手剣
	enWeaponLongSword,		//両手剣
	enWeaponArrow,			//弓矢
	enWeaponTwinSword,		//二刀
	enWeaponNum,
	enInvalid			//何もない
};


//武器のステータス
struct SWeaponStatus
{
	int attack = 0;							//攻撃力
	int diffence = 0;						//防御力
	EnPlayerWeapon weaponNum = enInvalid;	//武器の種類
};