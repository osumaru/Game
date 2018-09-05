#include "stdafx.h"
#include "../Scene/GameScene.h"
#include "Map/Map.h"
#include "../Player/Player.h"
#include "../UI/MiniMap/MiniMap.h"
#include "../UI/WeaponSelect/WeaponSelect.h"
#include "../UI/PlayerHp/PlayerHp.h"
#include "../UI/Menu/Menu.h"
void CGameScene::Init()


{
	map = New<Map>(0);
	map->Init(0);


	CMenu* menu = New<CMenu>(0);
	menu->Init();

	CMiniMap* miniMap = New<CMiniMap>(0);
	miniMap->Init();



	damageNumber.Init();

	CWeaponSelect* weaponSelect = New<CWeaponSelect>(0);
	weaponSelect->Init();

	CPlayerHp* playerHp = New<CPlayerHp>(0);
	playerHp->Init();

	
}

void CGameScene::Update()
{
	//ダメージ計算
	//damageNumber.DamageCalculation(&GetPlayer().GetInstance(), map->GetEnemy());

}
