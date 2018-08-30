#pragma once

class Player;
class Enemy;
#include "Number.h"

class DamegeNumber
{
public:
	void Init();

	void DamageCalculation(Player* player, Enemy* enemy);

private:
	Number* m_number[3];
	Vector2 m_numPos;
	Vector2 m_numSize;
};