#pragma once
//武器の種類の列挙型
enum EnPlayerWeapon
{
	enWeaponSword,			//片手剣
	enWeaponLongSword,		//両手剣
	enWeaponArrow,			//弓矢
	enWeaponTwinSword,		//二刀
	enWeaponNum,			//武器の数
	enInvalid			//何もない
};

//enum EnAttackWeapon
//{
//	enAttackWeaponLongSword,
//	enAttackWeaponSword,
//	enAttackWeaponRightSword,
//	enAttackWeaponLeftSword,
//	enAttackWeaponArrow,
//	enAttackWeaponNone,
//	enAttackWeaponNum
//};

//武器のステータス
struct SWeaponStatus
{
	int attack = 0;							//攻撃力
	int diffence = 0;						//防御力
	EnPlayerWeapon weaponNum = enInvalid;	//武器の種類
};

struct SWeaponEnemyAttackInfo
{
	bool		isAttack = false;	//攻撃モーション中攻撃の判定をするかのフラグ(遠距離の武器もあるため
	CVector3	attackPos[2];		//当たり判定用の座標
};

struct SWeaponTraceDrawInfo
{
	bool		isDraw = false;				//描画するかのフラグ
	CVector3	rootPos[2];					//武器の根っこ
	CVector3	pointPos[2];				//武器の先っちょ
};