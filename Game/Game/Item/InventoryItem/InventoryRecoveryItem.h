/*
*	インベントリに入れる回復アイテムクラス
*/

#pragma once

#include "IInventoryItem.h"

class CInventoryRecoveryItem : public IInventoryItem
{
public:
	//初期化
	void Init() override;

	//描画
	void Draw() override;

	//アイテムを使う
	bool Use() override;

private:
	int m_recoveryValue = 30;	//回復値
};