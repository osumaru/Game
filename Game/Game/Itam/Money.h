/*
*	お金のアイテムクラス
*/

#pragma once

#include "IItem.h"

class CMoney : public IItem
{
public:
	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

	//移動
	void Move();
};