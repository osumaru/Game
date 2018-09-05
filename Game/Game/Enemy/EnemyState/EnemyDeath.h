/*
*	エネミーの死亡クラス
*/

#pragma once

#include "IEnemyState.h"

class EnemyDeath : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	EnemyDeath(IEnemy* enemy, EnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~EnemyDeath() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:

};