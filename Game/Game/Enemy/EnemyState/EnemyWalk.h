/*
*	エネミーの歩きクラス
*/

#pragma once

#include "IEnemyState.h"

class EnemyWalk : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	EnemyWalk(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~EnemyWalk() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:
	CVector3	m_destination;
	const float m_speed = 2.0f;
};