#pragma once

class Map;
#include "../UI/DamageNumber/DamageNumber.h"

class CGameScene : public GameObject
{
public:
	void Init();

	void Update();

private:
	Map* map = nullptr;
	CDamegeNumber damageNumber;
};