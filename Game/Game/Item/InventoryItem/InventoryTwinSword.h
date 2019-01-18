/*
*	インベントリに入れる用の双剣
*/

#pragma once

#include "IInventoryEquip.h"

class CInventoryTwinSword : public IInventoryEquip
{
public:
	//初期化
	//itemName			アイテムの名前
	//textureFilePath	テクスチャのファイルパス
	void Init(const wchar_t* itemName, const wchar_t* textureFilePath) override;

	//描画
	void Draw() override;
};