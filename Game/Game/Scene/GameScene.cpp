#include "stdafx.h"
#include "../Scene/GameScene.h"
#include "Map/Map.h"
#include "../Player/Player.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/WeaponSelect/WeaponSelect.h"
#include "../UI/PlayerHp/PlayerHp.h"
#include "../UI/Menu/Menu.h"
void GameScene::Init()

{
	map = New<Map>(0);
	map->Init(0);

	CMenu* menu = New<CMenu>(0);
	menu->Init();

	MiniMap* miniMap = New<MiniMap>(0);
	miniMap->Init();



	damageNumber.Init();

	WeaponSelect* weaponSelect = New<WeaponSelect>(0);
	weaponSelect->Init();

	PlayerHp* playerHp = New<PlayerHp>(0);
	playerHp->Init();

	
}

void GameScene::Update()
{
	damageNumber.DamageCalculation(&GetPlayer().GetInstance(), map->GetEnemy());
	
}
