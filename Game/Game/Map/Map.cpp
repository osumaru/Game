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
#include "MapChip/Castle.h"
#include "MapChip/Tree.h"
#include "../NPC/IShop.h"

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
		#include "Boss.h"
	},
	{
		#include "TitleMap.h"
	}
};
	
Map::Map()
{
}

Map::~Map()
{

}

void Map::Init(int stageNum)
{
	std::map<int, std::vector<SMapChipInfo>> instancingData;
	std::list<IGameObject*> mapChips;
	CVector3 aabbMax = { FLT_MIN, FLT_MIN, FLT_MIN };
	CVector3 aabbMin = { FLT_MAX, FLT_MAX, FLT_MAX };
	m_shopManager = New<CShopManager>(PRIORITY_SHOP);

	for (SMapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		aabbMax.Max(mInfo.m_position);
		aabbMin.Min(mInfo.m_position);
	}
	m_partitionRange = 0.0f;
	const int ELEMENT_NUM = 2;
	float length[ELEMENT_NUM] = { aabbMax.x - aabbMin.x, aabbMax.z - aabbMin.z};
	for (int i = 0; i < ELEMENT_NUM; i++)
	{
		m_partitionRange = max(m_partitionRange, length[i] / AREA_PARTITION_NUM);
	}

	for (SMapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		MapChip* mapChip = nullptr;
		CEnemyGroup* enemyGroup = nullptr;
		CTreasureChest* treasureChest = nullptr;
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
			mapChip = New<CZombie>(PRIORITY_ENEMY);
			break;
		case enMapTagNinja:
			mapChip = New<CNinja>(PRIORITY_ENEMY);
			break;
		case enMapTagSamurai:
			mapChip = New<CSamurai>(PRIORITY_ENEMY);
			break;
		case enMapTagWarrok:
			mapChip = New<CWarrok>(PRIORITY_ENEMY);
			break;
		case enMapTagEnemyGroup:
			enemyGroup = New<CEnemyGroup>(PRIORITY_ENEMY);
			enemyGroup->Init(mInfo.m_position);
			m_enemyGroupList.push_back(enemyGroup);
			break;
		case enMapTagTreasureBox:
			treasureChest = New<CTreasureChest>(PRIORITY_ITEM);
			treasureChest->Init(mInfo.m_position,mInfo.m_rotation, true);
			treasureChest->SetWeaponQuality((EnItemQuality)mInfo.m_dropType);
			break;
		case enMapTagItemShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enItemShop);
			break;
		case enMapTagWeaponShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enWeaponShop);
			break;
		case enMapTagNormalShop:
			m_shopManager->InitShop(mInfo.m_position, mInfo.m_rotation, EShop::enNormalNpc);
			break;
		case enMapTagTree:
			mapChip = New<CTree>(PRIORITY_MAPCHIP);
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
			break;
		case enMapTagSoundPoint:
			mapChip = New<CCastle>(PRIORITY_BILLDING);
			GetSceneManager().GetGameSound()->SetTownPosition(mInfo.m_position);
			break;
		case enMapTagTerrain:
			m_ground = New<StaticMapObject>(PRIORITY_GROUND);
			m_ground->Init(mInfo);
			m_ground->Hoge();
			g_pathFinding.GetNavigationMesh().SetSkinModel(&dynamic_cast<StaticMapObject*>(m_ground)->GetSkinModel());
			break;
		case enMapTagMesh:
			mapChip = New<StaticMapObject>(PRIORITY_GROUND);
			break;
		case enMapTagCastle:
			mapChip = New<CCastle>(PRIORITY_BILLDING);
			break;
		case enMapTagObstacle:
			mapChip = New<CObstacleMapObject>(PRIORITY_BILLDING);
			break;
		default:
			mapChip = New<StaticMapObject>(PRIORITY_MAPCHIP);
			break;
		}
		if (mapChip != nullptr)
		{
			//マップチップを生成
			mapChip->Init(mInfo);
			CVector3 areaPos = mInfo.m_position;
			areaPos.x += m_partitionRange * (AREA_PARTITION_NUM / 2);
			areaPos.z += m_partitionRange * (AREA_PARTITION_NUM / 2);
			areaPos.x /= m_partitionRange;
			areaPos.z /= m_partitionRange;
			int areaX = min(max((int)areaPos.x, 0), AREA_PARTITION_NUM - 1);
			int areaY = min(max((int)areaPos.z, 0), AREA_PARTITION_NUM - 1);

			m_mapChips[areaX][areaY].push_back(mapChip);

			//マップチップに自身のイテレーターとマップのインスタンスを渡す(削除の時に使う)
			std::list<MapChip*>::iterator iterator = m_mapChips[areaX][areaY].end();
			iterator--;
			mapChip->SetIterator(this, iterator, areaX, areaY);
		}
	}

	Add(&Sky(), PRIORITY_SKY);
	g_pathFinding.BuildNodes();
	
}


void Map::Update()
{
	if (&GetPlayer() == nullptr)
	{
		return;
	}
	CVector3 playerPos = GetPlayer().GetPosition();
	int playerAreaPosX = GetAreaPosX(playerPos);
	int playerAreaPosY = GetAreaPosY(playerPos);
	if (m_playerAreaPosX != playerAreaPosX ||
		m_playerAreaPosY != playerAreaPosY)
	{
		m_playerAreaPosX = playerAreaPosX;
		m_playerAreaPosY = playerAreaPosY;
		for (int i = 0; i < AREA_PARTITION_NUM; i++)
		{
			for (int j = 0; j < AREA_PARTITION_NUM; j++)
			{
				for (auto& mapChip : m_mapChips[i][j])
				{
					mapChip->SetIsActiveUpdate(false);
				}
			}
		}
		const int AREA_NUM = 9;
		int areaPosX[AREA_NUM] = { m_playerAreaPosX,m_playerAreaPosX, m_playerAreaPosX,
							m_playerAreaPosX + 1, m_playerAreaPosX + 1, m_playerAreaPosX + 1,
							m_playerAreaPosX - 1, m_playerAreaPosX - 1, m_playerAreaPosX - 1, };
		int areaPosY[AREA_NUM] = { m_playerAreaPosY,m_playerAreaPosY + 1, m_playerAreaPosY - 1,
							m_playerAreaPosY, m_playerAreaPosY + 1, m_playerAreaPosY - 1,
							m_playerAreaPosY, m_playerAreaPosY + 1, m_playerAreaPosY - 1, };
		for (int i = 0; i < AREA_NUM; i++)
		{
			areaPosX[i] = max(0, min(AREA_PARTITION_NUM - 1, areaPosX[i]));
			areaPosY[i] = max(0, min(AREA_PARTITION_NUM - 1, areaPosY[i]));
			for (auto& mapChip : m_mapChips[areaPosX[i]][areaPosY[i]])
			{
				mapChip->SetIsActiveUpdate(true);
			}
		}
	}
}


void Map::MapChipErase(std::list<MapChip*>::iterator iterator, int areaPosX, int areaPosY)
{
	Delete(*iterator);
	m_mapChips[areaPosX][areaPosY].erase(iterator);
}

void Map::SetIsMapChipActiveUpdate(bool isActive)
{

	for (int i = 0; i < AREA_PARTITION_NUM; i++)
	{
		for (int j = 0; j < AREA_PARTITION_NUM; j++)
		{
			for (auto& mapChip : m_mapChips[i][j])
			{
				mapChip->SetIsActiveUpdate(false);
			}
		}
	}
	if (isActive)
	{
		const int AREA_NUM = 9;
		int areaPosX[AREA_NUM] = { m_playerAreaPosX,m_playerAreaPosX, m_playerAreaPosX,
							m_playerAreaPosX + 1, m_playerAreaPosX + 1, m_playerAreaPosX + 1,
							m_playerAreaPosX - 1, m_playerAreaPosX - 1, m_playerAreaPosX - 1, };
		int areaPosY[AREA_NUM] = { m_playerAreaPosY,m_playerAreaPosY + 1, m_playerAreaPosY - 1,
							m_playerAreaPosY, m_playerAreaPosY + 1, m_playerAreaPosY - 1,
							m_playerAreaPosY, m_playerAreaPosY + 1, m_playerAreaPosY - 1, };
		for (int i = 0; i < AREA_NUM; i++)
		{
			areaPosX[i] = max(0, min(AREA_PARTITION_NUM - 1, areaPosX[i]));
			areaPosY[i] = max(0, min(AREA_PARTITION_NUM - 1, areaPosY[i]));
			for (auto& mapChip : m_mapChips[areaPosX[i]][areaPosY[i]])
			{
				mapChip->SetIsActiveUpdate(true);
			}
		}
	}
	//敵グループクラスのアクティブ設定
	for (auto& enemyGroup : m_enemyGroupList)
	{
		enemyGroup->SetIsActiveUpdate(isActive);
	}
	for (auto& shop : m_shopManager->Getlist())
	{
		shop->SetIsActiveUpdate(isActive);
	}
	//ボスの動きの設定
	if (&GetMaw())
	{
		GetMaw().SetIsActiveUpdate(isActive);
	}
	//プレイヤーの動きの設定
	if (&GetPlayer())
	{
		GetPlayer().SetIsActiveUpdate(isActive);
	}
}

void Map::CreateMapChip(const SMapChipInfo& info)
{
	MapChip* mapChip = nullptr;
	CEnemyGroup* enemyGroup = nullptr;
	CTreasureChest* treasureChest = nullptr;
	IEnemy* enemy = nullptr;
	CBossBuilding* bossBuilding = nullptr;
	CSea* sea = nullptr;
	CTitleEnemy* titleEnemy = nullptr;
	switch (info.m_tag)
	{
	case enMapTagMapChip:
		mapChip = New<MapChip>(PRIORITY_MAPCHIP);
		break;
	case enMapTagPlayer:
		GetPlayer().Create();
		GetPlayer().Init(info.m_position);
		break;
	case enMapTagMaw:
		GetMaw().Create();
		GetMaw().Init(info.m_position);
		break;
	case enMapTagZombie:
		mapChip = New<CZombie>(PRIORITY_ENEMY);
		break;
	case enMapTagNinja:
		mapChip = New<CNinja>(PRIORITY_ENEMY);
		break;
	case enMapTagSamurai:
		mapChip = New<CSamurai>(PRIORITY_ENEMY);
		break;
	case enMapTagWarrok:
		mapChip = New<CWarrok>(PRIORITY_ENEMY);
		break;
	case enMapTagEnemyGroup:
		enemyGroup = New<CEnemyGroup>(PRIORITY_ENEMY);
		enemyGroup->Init(info.m_position);
		m_enemyGroupList.push_back(enemyGroup);
		break;
	case enMapTagTreasureBox:
		treasureChest = New<CTreasureChest>(PRIORITY_ITEM);
		treasureChest->Init(info.m_position, info.m_rotation, true);
		treasureChest->SetWeaponQuality((EnItemQuality)info.m_dropType);
		break;
	case enMapTagItemShop:
		m_shopManager->InitShop(info.m_position, info.m_rotation, EShop::enItemShop);
		break;
	case enMapTagWeaponShop:
		m_shopManager->InitShop(info.m_position, info.m_rotation, EShop::enWeaponShop);
		break;
	case enMapTagNormalShop:
		m_shopManager->InitShop(info.m_position, info.m_rotation, EShop::enNormalNpc);
		break;
	case enMapTagTree:
		mapChip = New<CTree>(PRIORITY_MAPCHIP);
		break;
	case enMapTagTitleEnemy:
		titleEnemy = New<CTitleEnemy>(PRIORITY_ENEMY);
		titleEnemy->Init(info.m_modelName, info.m_position);
		break;
	case enMapTagSea:
		sea = New<CSea>(PRIORITY_BILLDING);
		sea->Init(info.m_position, info.m_rotation);
		break;
	case enMapTagBossObj:
		bossBuilding = New<CBossBuilding>(PRIORITY_BILLDING);
		bossBuilding->Init(info.m_position, info.m_rotation);
		break;
	case enMapTagBreakBrock:
		mapChip = New<CBreakMapObject>(PRIORITY_MAPCHIP);
		break;
	case enMapTagSoundPoint:
		mapChip = New<CCastle>(PRIORITY_BILLDING);
		GetSceneManager().GetGameSound()->SetTownPosition(info.m_position);
		break;
	case enMapTagTerrain:
		m_ground = New<StaticMapObject>(PRIORITY_GROUND);
		m_ground->Init(info);
		g_pathFinding.GetNavigationMesh().SetSkinModel(&dynamic_cast<StaticMapObject*>(m_ground)->GetSkinModel());
		break;
	case enMapTagMesh:
		mapChip = New<StaticMapObject>(PRIORITY_GROUND);
		break;
	case enMapTagCastle:
		mapChip = New<CCastle>(PRIORITY_BILLDING);
		break;
	case enMapTagObstacle:
		mapChip = New<CObstacleMapObject>(PRIORITY_BILLDING);
		break;
	default:
		mapChip = New<StaticMapObject>(PRIORITY_MAPCHIP);
		break;
	}
	if (mapChip != nullptr)
	{
		//マップチップを生成
		mapChip->Init(info);
		CVector3 areaPos = info.m_position;
		areaPos.x += m_partitionRange * (AREA_PARTITION_NUM / 2);
		areaPos.z += m_partitionRange * (AREA_PARTITION_NUM / 2);
		areaPos.x /= m_partitionRange;
		areaPos.z /= m_partitionRange;
		int areaX = min(max((int)areaPos.x, 0), AREA_PARTITION_NUM - 1);
		int areaY = min(max((int)areaPos.z, 0), AREA_PARTITION_NUM - 1);

		m_mapChips[areaX][areaY].push_back(mapChip);

		//マップチップに自身のイテレーターとマップのインスタンスを渡す(削除の時に使う)
		std::list<MapChip*>::iterator iterator = m_mapChips[areaX][areaY].end();
		iterator--;
		mapChip->SetIterator(this, iterator, areaX, areaY);
	}
}

void Map::BeforeDead()
{
	//ボスが作られていなかったら
	if (&GetMaw() != NULL)
	{
		GetMaw().Destroy();
	}
	for (int i = 0; i < AREA_PARTITION_NUM; i++)
	{
		for (int j = 0; j < AREA_PARTITION_NUM; j++)
		{
			for (IGameObject* obj : m_mapChips[i][j])
			{
				Delete(obj);
			}
			m_mapChips[i][j].clear();
		}
	}
	if (m_ground != nullptr)
	{
		Delete(m_ground);
	}
	//NPCの消去
	m_shopManager->DeleteList();
	Delete(m_shopManager);

	//エネミーグループの消去
	for (CEnemyGroup* enemygroup : m_enemyGroupList)
	{
		Delete(enemygroup);
	}
	m_enemyGroupList.clear();


	if (&GetPlayer() != nullptr) 
	{
		//プレイヤーの消去
		GetPlayer().Destroy();
	}
	Delete(&Sky());

}