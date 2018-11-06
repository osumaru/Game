/*
*	装備アイテムクラス
*/

#pragma once

#include "IItem.h"
#include "../Player/Weapon.h"

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
private:
	CWeapon::SWeaponStatus m_weaponStatus;	//武器のステータス
};