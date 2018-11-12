/*
*	エネミーのステートのインターフェース
*/

#pragma once

#include "stdafx.h"

class IEnemy;
class CEnemyStateMachine;
class CEnemyGroup;

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

	//解放
	virtual void Release() {};

	//所属するグループを設定
	//enemyGroup	所属するグループのポインタ
	void SetEnemyGroup(CEnemyGroup* enemyGroup)
	{
		m_enemyGroup = enemyGroup;
	}

protected:
	IEnemy*				m_enemy = nullptr;		//エネミー
	CEnemyStateMachine*	m_esm = nullptr;		//ステートマシン
	CEnemyGroup*		m_enemyGroup = nullptr;	//エネミーグループ
};