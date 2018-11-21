/*
*	お金のアイテムクラス
*/

#pragma once

#include "IItem.h"

class CMoney : public IItem
{
public:
	//初期化
	//gold	お金の値
	void Init(const int gold);

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//ポップさせる
	//position	座標
	void Pop(CVector3 position);

private:
	int m_gold = 0;	//お金の値
};