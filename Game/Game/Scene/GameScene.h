#pragma once

class Map;
#include "../UI/DamageNumber/DamageNumber.h"

class GameScene : public GameObject
{
public:
	void Init();

	void Update();

private:
	Map* map = nullptr;
	DamegeNumber damageNumber;
};