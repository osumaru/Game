/*
*	エネミーの追従クラス
*/

#pragma once

#include "IEnemyState.h"

class CEnemyChase : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyChase(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyChase() {}

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	void Move(float length);

private:
	int	m_interval = 0;	//インターバル
};
