/*
*	インベントリに入れる用の双剣
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryTwinSword : public IInventoryEquip
{
public:
	//初期化
	void Init() override;

	//描画
	void Draw() override;
};