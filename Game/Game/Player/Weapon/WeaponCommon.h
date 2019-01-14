#pragma once
//•Ší‚Ìí—Ş‚Ì—ñ‹“Œ^
enum EnPlayerWeapon
{
	enWeaponSword,			//•ĞèŒ•
	enWeaponLongSword,		//—¼èŒ•
	enWeaponArrow,			//‹|–î
	enWeaponTwinSword,		//“ñ“
	enWeaponNum,			//•Ší‚Ì”
	enInvalid			//‰½‚à‚È‚¢
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

//•Ší‚ÌƒXƒe[ƒ^ƒX
struct SWeaponStatus
{
	int attack = 0;							//UŒ‚—Í
	int diffence = 0;						//–hŒä—Í
	EnPlayerWeapon weaponNum = enInvalid;	//•Ší‚Ìí—Ş
};

//•Ší‚ÌŠî–{UŒ‚—Í
const struct SBasicWeaponStatus 
{
	int basicAttack = 100;		//Šî–{UŒ‚—Í
	int swordAttack = 50;		//Œ•‚ÌUŒ‚—Í
	int longSwordAttack = 70;	//‘åŒ•‚ÌUŒ‚—Í
	int arrowAttack = 20;		//‹|‚ÌUŒ‚—Í
	int twinSwordAttack = 30;	//‘oŒ•‚ÌUŒ‚—Í
};

struct SWeaponEnemyAttackInfo
{
	bool		isAttack = false;	//UŒ‚ƒ‚[ƒVƒ‡ƒ“’†UŒ‚‚Ì”»’è‚ğ‚·‚é‚©‚Ìƒtƒ‰ƒO(‰“‹——£‚Ì•Ší‚à‚ ‚é‚½‚ß
	CVector3	attackPos[2];		//“–‚½‚è”»’è—p‚ÌÀ•W
};

struct SWeaponTraceDrawInfo
{
	bool		isDraw = false;				//•`‰æ‚·‚é‚©‚Ìƒtƒ‰ƒO
	CVector3	rootPos[2];					//•Ší‚Ìª‚Á‚±
	CVector3	pointPos[2];				//•Ší‚Ìæ‚Á‚¿‚å
};