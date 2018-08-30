#include "stdafx.h"
#include "../Scene/GameScene.h"
#include "Map/Map.h"
#include "../Player/Player.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/WeaponSelect/WeaponSelect.h"

void GameScene::Init()
{
	map = New<Map>(0);
	map->Init(0);

	MiniMap* miniMap = New<MiniMap>(0);
	miniMap->Init();

	damageNumber.Init();

	WeaponSelect* weaponSelect = New<WeaponSelect>(0);
	weaponSelect->Init();
}

void GameScene::Update()
{
	damageNumber.DamageCalculation(&GetPlayer().GetInstance(), map->GetEnemy());
}
