#pragma once

#include "IEnemyState.h"

class EnemyWalk : public IEnemyState
{
public:
	EnemyWalk(IEnemy* enemy, EnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	~EnemyWalk() {}

	bool Start();

	void Update();

private:

};