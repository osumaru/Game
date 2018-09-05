/*
*	敵のインターフェースクラス
*/

#pragma once

#include "EnemyStateMachine.h"

class IEnemy : public IGameObject
{
public:
	//コンストラクタ
	IEnemy();

	//デストラクタ
	~IEnemy();

	//初期化
	virtual void Init(CVector3 position) = 0;

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() = 0;
};