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
	bool Start() override;

	//更新
	void Update() override;

	//アニメーションが終了したか
	bool GetIsAnimationEnd()
	{
		return m_isAnimationEnd;
	}

private:
	bool m_isAnimationEnd = false;	//アニメーションが終了したか
};