#pragma once

#include "IEnemyState.h"

class EnemyIdle : public IEnemyState 
{
public:
	EnemyIdle(IEnemy* enemy, EnemyStateMachine* esm):
		IEnemyState(enemy, esm)
	{
	}

	~EnemyIdle() {}

	bool Start();

	void Update();

private:

};