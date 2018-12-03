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
private:
	CDamageNumber*	m_damageNumber = nullptr;	//ダメージ表示
	const float		m_knockBackSpeed = 3.0f;	//ノックバックスピード
	float			m_friction = 0.5f;			//摩擦
	int				m_debugDamageCount = 0;
};