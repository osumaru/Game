/*
*	インベントリに入れる用の弓
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryBow : public IInventoryEquip
{
public:
	//初期化
	void Init() override;

	//描画
	void Draw() override;
};