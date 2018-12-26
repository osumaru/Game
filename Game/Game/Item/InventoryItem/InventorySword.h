/*
*	インベントリに入れる用の剣
*/

#pragma once

#include "IInventoryEquip.h"

class CInventorySword : public IInventoryEquip
{
public:
	//初期化
	void Init() override;

	//描画
	void Draw() override;
};