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

std::vector<std::vector<SMapChipInfo>> mapChipInfo = 
{
	{
#include "Location.h"
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

	for (SMapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		MapChip* mapChip = nullptr;
		CEnemyGroup* enemyGroup = nullptr;
		IEnemy* enemy = nullptr;

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
		default:
			mapChip = New<StaticMapObject>(0);
			break;
		}
		if (mapChip != nullptr)
		{
			//�}�b�v�`�b�v�𐶐�
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName);
			m_mapChip.push_back(mapChip);
			//�}�b�v�`�b�v�Ɏ��g�̃C�e���[�^�[�ƃ}�b�v�̃C���X�^���X��n��(�폜�̎��Ɏg��)
			std::list<MapChip*>::iterator iterator = m_mapChip.end();
			iterator--;
			mapChip->SetIterator(this, iterator);
		}
	}

	//��������O���[�v�����߂�
	for (IEnemy* enemy : m_enemyList) 
	{
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
	}
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
	//Delete(m_player);
	for (MapChip* mapchip : m_mapChip)
	{
		Delete(mapchip);
	}
	m_mapChip.clear();

}