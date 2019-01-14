/*
*	エネミーのステートマシン
*/

#pragma once

#include "EnemyIdle.h"
#include "EnemyWalk.h"
#include "EnemyChase.h"
#include "EnemyAttack.h"
#include "EnemyDamage.h"
#include "EnemyDeath.h"
#include "EnemyStan.h"
#include "EnemyAttackWait.h"
#include "IEnemyState.h"
#include "EnemyState.h"

class CEnemyGroup;

class CEnemyStateMachine : public IGameObject
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	CEnemyStateMachine(IEnemy* enemy) :
		m_enemyIdle(enemy, this),
		m_enemyWalk(enemy, this),
		m_enemyChase(enemy, this),
		m_enemyAttack(enemy, this),
		m_enemyDamage(enemy, this),
		m_enemyDeath(enemy, this),
		m_enemyStan(enemy, this),
		m_enemyAttackWait(enemy, this)
	{
	}

	//デストラクタ
	virtual ~CEnemyStateMachine() {}

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//ステートの切り替え
	void ChangeState(CEnemyState::EnState nextState);

	//解放
	void Release();

	//所属するグループを設定
	//enemyGroup		所属するグループのポインタ
	void SetEnemyGroup(CEnemyGroup* enemyGroup)
	{
		m_enemyGroup = enemyGroup;
	}

	//ステートを取得
	const IEnemyState* GetState(CEnemyState::EnState state) const
	{
		switch (state)
		{
		case CEnemyState::enState_Attack:
			return &m_enemyAttack;

		case CEnemyState::enState_AttackWait:
			return &m_enemyAttackWait;

		case CEnemyState::enState_Chase:
			return &m_enemyChase;

		case CEnemyState::enState_Damage:
			return &m_enemyDamage;

		case CEnemyState::enState_Death:
			return &m_enemyDeath;

		case CEnemyState::enState_Idle:
			return &m_enemyIdle;

		case CEnemyState::enState_Stan:
			return &m_enemyStan;

		case CEnemyState::enState_Walk:
			return &m_enemyWalk;
		}
	}

private:
	CEnemyState::EnState	m_state = CEnemyState::enState_Invald;	//エネミーの状態
	IEnemyState*			m_currentState = nullptr;				//現在の状態
	CEnemyIdle				m_enemyIdle;							//待機
	CEnemyWalk				m_enemyWalk;							//歩き
	CEnemyChase				m_enemyChase;							//追従
	CEnemyAttack			m_enemyAttack;							//攻撃
	CEnemyDamage			m_enemyDamage;							//ダメージ
	CEnemyDeath				m_enemyDeath;							//死亡
	CEnemyStan				m_enemyStan;							//スタン
	CEnemyAttackWait		m_enemyAttackWait;						//攻撃後の待ち
	CEnemyGroup*			m_enemyGroup = nullptr;					//エネミーグループ
};