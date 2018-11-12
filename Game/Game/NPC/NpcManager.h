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
		enShopBuy,			//買い物を行うとき
		enShopExecute,		//店を出るとき
		enShopNone,			//何も行っていないとき
		enShopLineup,	
		enShopNum,
	};
	std::list<INpcState*>		m_npclist;

};

