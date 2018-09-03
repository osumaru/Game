#pragma once

class Map;
#include "../UI/DamageNumber/DamageNumber.h"

class CGameScene : public IGameObject
{
public:
	void Init();

	void Update();

private:
	Map* map = nullptr;
	CDamegeNumber damageNumber;
};