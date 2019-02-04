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
	//isMapItem		マップに配置するか
	void Init(CVector3 position, bool isMapItem);

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
	bool m_itemDrawCount = false;	//アイテムを拾うUIを出すカウントをすでにしているか
	bool m_isMapItem = false;		//マップに配置するか
};