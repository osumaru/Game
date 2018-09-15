/*
*	エネミーのステートのインターフェース
*/

#pragma once

#include "stdafx.h"

class IEnemy;
class CEnemyStateMachine;

class IEnemyState : public IGameObject
{
public:
	//コンストラクタ
	//enemy		エネミーのインターフェースクラスのポインタ
	//esm		エネミーのステートマシンクラスのポインタ
	IEnemyState(IEnemy* enemy, CEnemyStateMachine* esm) :
		m_enemy(enemy),
		m_esm(esm)
	{
	}

	//デストラクタ
	virtual ~IEnemyState() {}

	//更新
	virtual void Update() = 0;

protected:
	IEnemy*				m_enemy = nullptr;	//エネミー
	CEnemyStateMachine*	m_esm = nullptr;	//ステートマシン
};