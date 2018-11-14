/*
*	エネミーの歩きクラス
*/

#pragma once

#include "IEnemyState.h"

class CEnemyWalk : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyWalk(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyWalk() {}

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//移動
	void Move();
private:
	CVector3	m_destination;			//移動先の座標
	bool		m_isMoveEnd = false;	//移動が終わったか
};