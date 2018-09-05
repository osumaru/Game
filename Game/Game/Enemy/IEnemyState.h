/*
*	エネミーのステートのインターフェース
*/

#pragma once

#include "stdafx.h"

class IEnemy;
class EnemyStateMachine;

class IEnemyState : public IGameObject
{
public:
	//コンストラクタ
	IEnemyState(IEnemy* enemy, EnemyStateMachine* esm) :
		m_enemy(enemy),
		m_esm(esm)
	{
	}

	//デストラクタ
	~IEnemyState() {}

	//更新
	virtual void Update() = 0;

protected:
	IEnemy*				m_enemy = nullptr;	//エネミー
	EnemyStateMachine*	m_esm = nullptr;	//ステートマシン
};