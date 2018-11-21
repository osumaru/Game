/*
*	エネミーのスタンクラス
*/
#pragma once

#include "IEnemyState.h"

class CEnemyStan : public IEnemyState
{
public:
	CEnemyStan(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm) 
	{
	}

	~CEnemyStan()
	{
	}

	bool Start() override;

	void Update() override;
private:
	float m_timer = 0.0f;	//タイマー
};