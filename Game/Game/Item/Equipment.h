#pragma once

#include "IItem.h"

class CEquipment : public IItem
{
public:
	void Init();

	bool Start() override;

	void Update() override;

	void Draw() override;

	void Pop(CVector3 position);
private:

};