/*
*	エネミーのステートマシン
*/

#pragma once

#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "IEnemyState.h"
#include "EnemyState.h"

class EnemyStateMachine : public IGameObject
{
public:
	//コンストラクタ
	EnemyStateMachine(IEnemy* enemy) :
		m_enemyIdle(enemy, this),
		m_enemyWalk(enemy, this)
	{}

	//デストラクタ
	~EnemyStateMachine() {}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update() 
	{
	}

	//ステートの切り替え
	void ChangeState(EnemyState::EnState nextState);

	//解放
	void Release();

private:
	EnemyState::EnState m_state = EnemyState::enState_Invald;	//エネミーの状態
	IEnemyState*		m_currentState = nullptr;				//現在の状態
	EnemyIdle			m_enemyIdle;							//待機
	EnemyWalk			m_enemyWalk;							//歩き
};