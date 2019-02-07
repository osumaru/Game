#include "stdafx.h"
#include "Map.h"
#include "../GameSound/GameSound.h"
#include"../Scene/TitleScene.h"
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
#include "../Enemy/Boss/Maw.h"
#include "../Enemy/EnemyGroup.h"
#include "../Enemy/PathFinding/PathFinding.h"
#include"../NPC/ShopManager.h"
#include "../Map/BossBuilding.h"
#include "../Enemy/TitleEnemy.h"
#include "MapChip/CSea.h"
#include "../Scene/SceneManager.h"
#include "../Item/TreasureChest.h"

std::vector<std::vector<SMapChipInfo>> mapChipInfo = 
{
	{
		//本番用の世界のマップ
		//#include "WorldMap.h"
		#include "ShopTest.h"
		//#include "mm.h"
		//#include "BossStage.h"
		//#include "Boss.h"
	},
	{
		#include "bossTest.h"
	},
	{
		#include "TitleMap.h"
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

	m_shopManager = New<CShopManager>(PRIORITY_SHOP);

	for (SMapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		MapChip* mapChip = nullptr;
		CEnemyGroup* enemyGroup = nullptr;
		CTreasureChest* treasureChest = nullptr;
		IEnemy* enemy = nullptr;
		std::list<IEnemy*>::iterator it;
		CBossBuilding* bossBuilding = nullptr;
		CSea* sea = nullptr;
		CTitleEnemy* titleEnemy = nullptr;
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
		case enMapTagTreasureBox:
			treasureChest = New<CTreasureChest>(PRIORITY_ENEMY);
			treasureChest->Init(mInfo.m_position,mInfo.m_rotation, true,(CTreasureChest::EnDropType)mInfo.m_dropType);
			m_treasureList.push_back(treasureChest);
			break;
		case enMapTagItemShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enItemShop);
			break;
		case enMapTagWeaponShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enWeaponShop);
			break;
		case enMapTagTree:
			mapChip = New<StaticMapObject>(PRIORITY_MAPCHIP);
			m_isTree = true;
			break;
		case enMapTagTitleEnemy:
			titleEnemy = New<CTitleEnemy>(PRIORITY_ENEMY);
			titleEnemy->Init(mInfo.m_modelName, mInfo.m_position);
			break;
		case enMapTagSea:
			sea = New<CSea>(PRIORITY_BILLDING);
			sea->Init(mInfo.m_position, mInfo.m_rotation);
			break;
		case enMapTagBossObj:
			bossBuilding = New<CBossBuilding>(PRIORITY_BILLDING);
			bossBuilding->Init(mInfo.m_position,mInfo.m_rotation);
			break;
		case enMapTagBreakBrock:
			mapChip = New<CBreakMapObject>(PRIORITY_MAPCHIP);
			m_collider = true;
			break;
		case enMapTagTerrain:
			mapChip = New<StaticMapObject>(PRIORITY_GROUND);
			g_pathFinding.GetNavigationMesh().SetSkinModel(&dynamic_cast<StaticMapObject*>(mapChip)->GetSkinModel());
			m_collider = false;
			break;
		case enMapTagMesh:
			mapChip = New<StaticMapObject>(PRIORITY_GROUND);
			m_collider = false;
			break;
		case enMapTagObstacle:
			mapChip = New<CObstacleMapObject>(PRIORITY_BILLDING);
			break;
		default:
			mapChip = New<StaticMapObject>(PRIORITY_MAPCHIP);
			m_collider = true;
			break;
		}
		if (enemy != nullptr)
		{
			enemy->Init(mInfo.m_position, mInfo.m_level);
			m_enemyList.push_back(enemy);
			it = m_enemyList.end();
			it--;
			enemy->SetIterater(it);
		}
		if (mapChip != nullptr)
		{
			//マップチップを生成
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName,m_isTree,m_collider);
			m_mapChip.push_back(mapChip);

			//マップチップに自身のイテレーターとマップのインスタンスを渡す(削除の時に使う)
			std::list<MapChip*>::iterator iterator = m_mapChip.end();
			iterator--;
			mapChip->SetIterator(this, iterator);
			m_isTree = false;
			m_collider = false;
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

	Add(&Sky(), PRIORITY_SKY);
	g_pathFinding.BuildNodes();
}


void Map::Update()
{
	if (Pad().IsTriggerButton(enButtonRB))
	{
		GetSceneManager().ChangeScene(CSceneManager::enBossScene);
	}
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

	for (auto* tresureList : m_treasureList)
	{
		Delete(tresureList);
	}
	m_treasureList.clear();

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

	if (&GetPlayer() != nullptr) 
	{
		//プレイヤーの消去
		GetPlayer().Destroy();
	}
	Delete(&Sky());

}