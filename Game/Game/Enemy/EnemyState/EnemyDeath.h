/*
*	エネミーの死亡クラス
*/

#pragma once

#include "IEnemyState.h"

class CEnemyDeath : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyDeath(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyDeath() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:

};