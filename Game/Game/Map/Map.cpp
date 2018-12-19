#include "stdafx.h"
#include "Map.h"
#include "MapChip/MapChip.h"
#include "MapChip\BreakMapObject.h"
#include "MapChip\StaticMapObject.h"
#include "MapChip/ObstacleMapObject.h"
#include "../Player/Player.h"
#include "../Enemy/IEnemy.h"
#include "../Enemy/Zombie.h"
#include "../Enemy/Ninja.h"
#include "../Enemy/Samurai.h"
#include "../Enemy/Warrok/Warrok.h"
#include "../Enemy/Maw.h"
#include "../Enemy/EnemyGroup.h"
#include "../Enemy/PathFinding/PathFinding.h"
#include"../NPC/ShopManager.h"


std::vector<std::vector<SMapChipInfo>> mapChipInfo = 
{
	{
	#include "alpha2.h"
	//#include "Boss.h"
	//#include "Test.h"
	//#include "ShopTest.h"
	//#include "Location2.h"
	}
};
	
Map::Map() :
	m_mapChip()
{
}

Map::~Map()
{

}

void Map::Init(int stageNum)
{
	std::map<int, std::vector<SMapChipInfo>> instancingData;

	//std::vector<CEnemyGroup*> enemyGroupList;
	m_shopManager = New<CShopManager>(PRIORITY_SHOP);

	for (SMapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		MapChip* mapChip = nullptr;
		CEnemyGroup* enemyGroup = nullptr;
		IEnemy* enemy = nullptr;
		std::list<IEnemy*>::iterator it;

		switch (mInfo.m_tag)
		{
		case enMapTagMapChip:
			mapChip = New<MapChip>(PRIORITY_MAPCHIP);
			break;
		case enMapTagPlayer:
			GetPlayer().Create();
			GetPlayer().Init(mInfo.m_position);
			break;
		case enMapTagMaw:
			GetMaw().Create();
			GetMaw().Init(mInfo.m_position);
			break;
		case enMapTagZombie:
			enemy = New<CZombie>(PRIORITY_ENEMY);
			break;
		case enMapTagNinja:
			enemy = New<CNinja>(PRIORITY_ENEMY);
			break;
		case enMapTagSamurai:
			enemy = New<CSamurai>(PRIORITY_ENEMY);
			break;
		case enMapTagWarrok:
			enemy = New<CWarrok>(PRIORITY_ENEMY);
			break;
		case enMapTagEnemyGroup:
			enemyGroup = New<CEnemyGroup>(PRIORITY_ENEMY);
			enemyGroup->Init(mInfo.m_position);
			m_enemyGroupList.push_back(enemyGroup);
			break;
		case enMapTagItemShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enItemShop);
			break;
		case enMapTagWeaponShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enWeaponShop);
			break;
		case enMapTagBreakBrock:
			mapChip = New<CBreakMapObject>(PRIORITY_MAPCHIP);
			m_collider = true;
			break;
		case enMapTagTerrain:
			mapChip = New<StaticMapObject>(PRIORITY_MAPCHIP);
			m_collider = false;
			break;
		case enMapTagObstacle:
			mapChip = New<CObstacleMapObject>(PRIORITY_MAPCHIP);
			break;
		default:
			mapChip = New<StaticMapObject>(PRIORITY_MAPCHIP);
			m_collider = true;
			break;
		}
		if (enemy != nullptr)
		{
			enemy->Init(mInfo.m_position);
			m_enemyList.push_back(enemy);
			it = m_enemyList.end();
			it--;
			enemy->SetIterater(it);
		}
		if (mapChip != nullptr)
		{
			//マップチップを生成
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName,m_collider);
			m_mapChip.push_back(mapChip);
			//マップチップに自身のイテレーターとマップのインスタンスを渡す(削除の時に使う)
			std::list<MapChip*>::iterator iterator = m_mapChip.end();
			iterator--;
			mapChip->SetIterator(this, iterator);
		}
	}

	for (IEnemy* enemy : m_enemyList) 
	{
		//所属するグループを決める
		CEnemyGroup* group = nullptr;
		for (CEnemyGroup* enemyGroup : m_enemyGroupList) {
			if (group == nullptr) 
			{
				group = enemyGroup;
				continue;
			}
			CVector3 distance = group->GetPosition();
			distance -= enemy->GetPosition();
			CVector3 distance2 = enemyGroup->GetPosition();
			distance2 -= enemy->GetPosition();
			if (distance2.Length() <= distance.Length()) 
			{
				group = enemyGroup;
			}
		}
		enemy->SetEnemyGroup(group);
		group->Add(enemy);
		enemy->AddObject();
	}
	
	g_pathFinding.BuildNodes();
}


void Map::Update()
{
}


void Map::MapChipErase(std::list<MapChip*>::iterator iterator)
{
	Delete(*iterator);
	iterator = m_mapChip.erase(iterator);
}

void Map::BeforeDead()
{
	//ボスが作られていなかったら
	if (&GetMaw() != NULL)
	{
		GetMaw().Destroy();
	}
	//マップチップの消去
	for (MapChip* mapchip : m_mapChip)
	{
		Delete(mapchip);
	}
	m_mapChip.clear();

	//NPCの消去
	m_shopManager->DeleteList();
	Delete(m_shopManager);

	//エネミーグループの消去
	for (CEnemyGroup* enemygroup : m_enemyGroupList)
	{
		Delete(enemygroup);
	}
	m_enemyGroupList.clear();

	//エネミーの消去
	for (IEnemy* enemy : m_enemyList)
	{
		Delete(enemy);
	}
	m_enemyList.clear();

	//プレイヤーの消去
	GetPlayer().Destroy();


}