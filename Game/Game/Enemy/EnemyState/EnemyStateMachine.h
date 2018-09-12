/*
*	エネミーのステートマシン
*/

#pragma once

#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDeath.h"
#include "IEnemyState.h"
#include "EnemyState.h"

class CEnemyStateMachine : public IGameObject
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	CEnemyStateMachine(IEnemy* enemy) :
		m_enemyIdle(enemy, this),
		m_enemyWalk(enemy, this),
		m_enemyAttack(enemy, this),
		m_enemyDamage(enemy, this),
		m_enemyDeath(enemy, this)
	{
	}

	//デストラクタ
	~CEnemyStateMachine() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update() 
	{
	}

	//ステートの切り替え
	void ChangeState(CEnemyState::EnState nextState);

	//解放
	void Release();

private:
	CEnemyState::EnState	m_state = CEnemyState::enState_Invald;	//エネミーの状態
	IEnemyState*			m_currentState = nullptr;				//現在の状態
	EnemyIdle				m_enemyIdle;							//待機
	EnemyWalk				m_enemyWalk;							//歩き
	EnemyAttack				m_enemyAttack;							//攻撃
	EnemyDamage				m_enemyDamage;							//ダメージ
	EnemyDeath				m_enemyDeath;							//死亡
};