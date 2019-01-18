/*
*	装備アイテムクラス
*/

#pragma once

#include "IItem.h"
#include "InventoryItem/IInventoryEquip.h"

class CTreasureChest : public IItem
{
public:
	//初期化
	//position		座標
	void Init(CVector3 position);

	//更新する前に一度だけ呼ばれる
	bool Start() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//武器のステータスを決める
	void DesideWeaponStatus();

private:
	std::unique_ptr<IInventoryEquip> m_inventoryEquip;	//インベントリに入れる装備

};