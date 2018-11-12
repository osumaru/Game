#pragma once
#include "Shop/ItemShop.h"
#include "Shop/WeaponShop.h"

enum EShop
{
	enItemShop,
	enWeaponShop,
	enWalkNpc,
};
class CNpcManager:public IGameObject
{
public:
	CNpcManager();
	~CNpcManager();
	void InitShop(const CVector3 position, const CQuaternion rotation, const EShop shopnum);
	void Update();
	void DeleteList();

private:
	enum EShopState
	{
		enShopBuy,			//”ƒ‚¢•¨‚ğs‚¤‚Æ‚«
		enShopExecute,		//“X‚ğo‚é‚Æ‚«
		enShopNone,			//‰½‚às‚Á‚Ä‚¢‚È‚¢‚Æ‚«
		enShopLineup,	
		enShopNum,
	};
	std::list<INpcState*>		m_npclist;

};

