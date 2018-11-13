/*
*	エネミーのダメージクラス
*/

#pragma once

#include "IEnemyState.h"

class CDamageNumber;

class CEnemyDamage : public IEnemyState
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	CEnemyDamage(IEnemy* enemy, CEnemyStateMachine* esm) :
		IEnemyState(enemy, esm)
	{
	}

	//デストラクタ
	~CEnemyDamage() {};

	//初期化
	void Init();

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//解放
	void Release() override;
private:
	CDamageNumber*	m_damageNumber = nullptr;	//ダメージ表示
	CVector3		m_knockBack;
	const float		m_knockBackSpeed = 1.0f;
};