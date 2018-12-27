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
	//武器の基本攻撃力
	const struct SBasicWeaponStatus 
	{
		int basicAttack = 100;		//基本攻撃力
		int swordAttack = 50;		//剣の攻撃力
		int longSwordAttack = 70;	//大剣の攻撃力
		int arrowAttack = 20;		//弓の攻撃力
		int twinSwordAttack = 30;	//双剣の攻撃力
	};

	std::unique_ptr<IInventoryEquip> m_inventoryEquip;
};