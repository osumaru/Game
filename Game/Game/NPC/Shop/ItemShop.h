#pragma once
#include "../INpcState.h"
#include "../../Item/QuickItem.h"
class CItemShop :public INpcState
{
public:
	CItemShop();
	~CItemShop();
	void Init(const CVector3 position, const CQuaternion rotation);
	void Update();
	void Draw();
	void AfterDraw();
private:
	CQuickItem		m_quickItem;

};

