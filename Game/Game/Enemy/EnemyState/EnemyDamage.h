/*
*	エネミーのダメージクラス
*/

#pragma once

#include "IEnemyState.h"

class EnemyDamage : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	EnemyDamage(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~EnemyDamage() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:
	float timer = 0.0f;		//タイマー
};