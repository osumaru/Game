#include "stdafx.h"
#include "Map.h"
#include "MapChip/MapChip.h"
#include "MapChip\StaticMapObject.h"
#include "../Player/Player.h"
#include "../Enemy/IEnemy.h"
#include "../Enemy/Zombie.h"
#include "../Enemy/Ninja.h"
#include "../Enemy/Samurai.h"
#include "../Enemy/Warrok.h"
#include "../Enemy/EnemyGroup.h"
#include "../Enemy/PathFinding/RootPoint.h"
#include "../Enemy/PathFinding/PathFinding.h"

std::vector<std::vector<SMapChipInfo>> mapChipInfo = 
{
	{
//#include "Location.h"
#include "Test.h"
	}
//	{
//#include "Location2.h"

//	},
//	{
//#include "Location3.h"
//	},

//	{
//#include "Location4.h"
//	},
//	{
//#include "Location5.h"
//	}
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

	std::vector<CEnemyGroup*> enemyGroupList;
	int rootNumber = 0;

	for (SMapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		MapChip* mapChip = nullptr;
		CEnemyGroup* enemyGroup = nullptr;
		IEnemy* enemy = nullptr;
		CRootPoint* rootPoint = nullptr;

		switch (mInfo.m_tag)
		{
		case enMapTagMapChip:
			mapChip = New<MapChip>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagPlayer:
			GetPlayer().Init(mInfo.m_position);
			break;
		case enMapTagZombie:
			enemy = New<CZombie>(1);
			enemy->Init(mInfo.m_position);
			m_enemyList.push_back(enemy);
			break;
		case enMapTagNinja:
			enemy = New<CNinja>(1);
			enemy->Init(mInfo.m_position);
			m_enemyList.push_back(enemy);
			break;
		case enMapTagSamurai:
			enemy = New<CSamurai>(1);
			enemy->Init(mInfo.m_position);
			m_enemyList.push_back(enemy);
			break;
		case enMapTagWarrok:
			enemy = New<CWarrok>(1);
			enemy->Init(mInfo.m_position);
			m_enemyList.push_back(enemy);
			break;
		case enMapTagEnemyGroup:
			enemyGroup = New<CEnemyGroup>(1);
			enemyGroup->Init(mInfo.m_position);
			enemyGroupList.push_back(enemyGroup);
			break;
		case enMapTagRootPoint:
			rootPoint = New<CRootPoint>(0);
			rootPoint->Init(mInfo.m_position, rootNumber);
			m_rootPointList.push_back(rootPoint);
			rootNumber++;
			break;
		case enMapTagTerrain:
			mapChip = New<StaticMapObject>(0);
			m_collider = false;
			break;
		default:
			mapChip = New<StaticMapObject>(0);
			m_collider = true;
			break;
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
		for (CEnemyGroup* enemyGroup : enemyGroupList) {
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

		//エネミーの初期位置に近いポイントを決める
		CRootPoint* point = nullptr;
		for (CRootPoint* rootPoint : m_rootPointList) {
			if (point == nullptr) 
			{
				point = rootPoint;
				continue;
			}
			CVector3 distance = point->GetPosition();
			distance -= enemy->GetPosition();
			CVector3 distance2 = rootPoint->GetPosition();
			distance2 -= enemy->GetPosition();
			if (distance2.Length() <= distance.Length()) 
			{
				point = rootPoint;
			}
		}
		enemy->SetRootPoint(point);
	}
	if (!m_rootPointList.empty()) {
		g_pathFinding.BuildNodes(m_rootPointList);
	}
}


void Map::Update()
{
	//エネミーが死亡していたらリストから削除
	std::list<IEnemy*>::iterator it;
	it = m_enemyList.begin();
	while (it != m_enemyList.end()) {
		if ((*it)->IsDelete()) {
			//死亡している
			IEnemy* enemy = *it;
			it = m_enemyList.erase(it);
		}
		else {
			it++;
		}
	}

	//エネミーのルート上のポイントを更新
	for (IEnemy* enemy : m_enemyList) {
		CRootPoint* point = nullptr;
		for (CRootPoint* rootPoint : m_rootPointList) {
			if (point == nullptr)
			{
				point = rootPoint;
				continue;
			}
			CVector3 distance = point->GetPosition();
			distance -= enemy->GetPosition();
			CVector3 distance2 = rootPoint->GetPosition();
			distance2 -= enemy->GetPosition();
			if (distance2.Length() <= distance.Length())
			{
				point = rootPoint;
			}
		}
		enemy->SetRootPoint(point);
	}

	CRootPoint* point = nullptr;
	for (CRootPoint* rootPoint : m_rootPointList) {
		if (point == nullptr)
		{
			point = rootPoint;
			continue;
		}
		CVector3 distance = point->GetPosition();
		distance -= GetPlayer().GetPosition();
		CVector3 distance2 = rootPoint->GetPosition();
		distance2 -= GetPlayer().GetPosition();
		if (distance2.Length() <= distance.Length())
		{
			point = rootPoint;
		}
	}
	GetPlayer().SetRootPoint(point);
}


void Map::MapChipErase(std::list<MapChip*>::iterator iterator)
{
	Delete(*iterator);
	iterator = m_mapChip.erase(iterator);
}

void Map::BeforeDead()
{
	//Delete(m_player);
	for (MapChip* mapchip : m_mapChip)
	{
		Delete(mapchip);
	}
	m_mapChip.clear();

}