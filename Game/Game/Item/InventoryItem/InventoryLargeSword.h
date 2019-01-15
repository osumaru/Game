/*
*	インベントリに入れる用の大剣
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryLargeSword : public IInventoryEquip
{
public:
	//初期化
	void Init(const wchar_t* itemName, const wchar_t* textureFileName) override;

	//描画
	void Draw() override;
};