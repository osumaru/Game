/*
*	エネミーの攻撃クラス
*/
#pragma once

#include "IEnemyState.h"

class CEnemyAttack : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyAttack(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyAttack() {}

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;
private:
	float	m_timer = 0.0f;		//タイマー
};