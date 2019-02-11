#pragma once
#include "ItemShop.h"
class CNormalShop : public IShop
{
public:
	CNormalShop();
	~CNormalShop();
	void Init(const CVector3 position, const CQuaternion rotation);
	void Update();
	void Draw();
};
