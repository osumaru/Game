/*
*	エネミーの攻撃後の待ち状態クラス
*/

#pragma once

#include "IEnemyState.h"

class CEnemyAttackWait : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyAttackWait(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyAttackWait()
	{
	}

	//更新される前に一度だけ呼ばれる関数
	bool Start() override;

	//更新
	void Update() override;

	//回転
	void Rotation();
private:
	float m_timer = 0.0f;	//タイマー
	bool  m_isNoneEnd = false; //何もしない状態が終わったか
};