/*
*	回復アイテムクラス
*/

#pragma once

#include "IItem.h"

class CRecoveryItem : public IItem
{
public:
	//初期化
	void Init(const CVector3& position);

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
};
