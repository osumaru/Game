/*
*	エネミーのスタンクラス
*/
#pragma once

#include "IEnemyState.h"

class CDamageNumber;

class CEnemyStan : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyStan(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm) 
	{
	}

	//デストラクタ
	~CEnemyStan()
	{
	}

	//更新される前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;
private:
	CDamageNumber*	m_damageNumber = nullptr;	//ダメージ表示
	float			m_timer = 0.0f;				//タイマー
};