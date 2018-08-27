#include "stdafx.h"
#include "Map.h"
#include "MapChip/MapChip.h"
#include "MapChip\StaticMapObject.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"


std::vector<std::vector<MapChipInfo>> mapChipInfo = 
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
	std::map<int, std::vector<MapChipInfo>> instancingData;
	Enemy* enemy = nullptr;
	for (MapChipInfo& mInfo : mapChipInfo[stageNum])
	{
		MapChip* mapChip = nullptr;

		switch (mInfo.m_tag)
		{
		case enMapTagMapChip:
			mapChip = New<MapChip>(STAGE_GIMMICK_PRIORITY);
			break;
		case enMapTagPlayer:
			GetPlayer().Init(mInfo.m_position);
			break;
		case enMapTagEnemy:
			enemy = New<Enemy>(0);
			enemy->Init(mInfo.m_position);
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