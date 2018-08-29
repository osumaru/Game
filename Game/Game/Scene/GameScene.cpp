#include "stdafx.h"
#include "../Scene/GameScene.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/DamageNumber/DamageNumber.h"
#include "../UI/WeaponSelect/WeaponSelect.h"

void GameScene::Init()
{
	MiniMap* miniMap = New<MiniMap>(0);
	miniMap->Init();

	DamegeNumber* damageNumber = New<DamegeNumber>(0);
	damageNumber->Init();

	WeaponSelect* weaponSelect = New<WeaponSelect>(0);
	weaponSelect->Init();
}

void GameScene::Update()
{

}
