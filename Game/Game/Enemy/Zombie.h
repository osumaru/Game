/*
*	ゾンビクラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class Zombie : public IEnemy
{
public:
	//コンストラクタ
	Zombie();

	//デストラクタ
	~Zombie();

	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新
	void Update();

	//描画
	void Draw();
};