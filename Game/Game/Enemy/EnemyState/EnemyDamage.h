/*
*	エネミーのダメージクラス
*/

#pragma once

#include "IEnemyState.h"
#include "../../UI/DamageNumber/DamageNumber.h"

class CEnemyDamage : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyDamage(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
		m_damageNumber.Init();
	}

	//デストラクタ
	~CEnemyDamage() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

private:
	CDamegeNumber	m_damageNumber;	//ダメージ数値
};