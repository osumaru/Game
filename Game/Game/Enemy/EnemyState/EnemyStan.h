/*
*	エネミーのスタンクラス
*/
#pragma once

#include "IEnemyState.h"

class CDamageNumber;

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
	CDamageNumber*	m_damageNumber = nullptr;	//ダメージ表示
	float m_timer = 0.0f;	//タイマー
};