#pragma once
#include "Shop/ItemShop.h"
#include "Shop/WeaponShop.h"

enum EShop
{
	enItemShop,
	enWeaponShop,
	enWalkNpc,
};
class CShopManager:public IGameObject
{
public:
	CShopManager();
	~CShopManager();
	void InitShop(const CVector3 position, const CQuaternion rotation, const EShop shopnum);
	void Update();
	void DeleteList();
	std::list<IShop*>& Getlist()
	{
		return m_shoplist;
	}
private:
	enum EShopState
	{
		enShopBuy,			//買い物を行うとき
		enShopExecute,		//店を出るとき
		enShopNone,			//何も行っていないとき
		enShopLineup,	
		enShopNum,
	};
	std::list<IShop*>		m_shoplist;

};

