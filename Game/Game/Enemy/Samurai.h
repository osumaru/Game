/*
*	侍クラス
*/

#pragma once

#include "Enemy/IEnemy.h"

class CSamurai : public IEnemy
{
public:
	//コンストラクタ
	CSamurai();

	//デストラクタ
	~CSamurai();

	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();
};