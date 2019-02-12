#pragma once
#include"../IShop.h"
#include "../../Item/GameItem/QuickItem.h"
class CItemShop :public IShop
{
public:
	CItemShop();
	~CItemShop();
	void Init(const CVector3 position, const CQuaternion rotation, EShop shopType);
	void Update();
	void Draw();
	void PostAfterDraw();
private:
	CQuickItem		m_quickItem;

};

