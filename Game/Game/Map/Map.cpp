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
		//�{�ԗp�̐��E�̃}�b�v
		//#include "WorldMap.h"
		//#include "ShopTest.h"
		#include "mm.h"
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
			mapChip = New<StaticMapObject>(PRIORITY_GROUND);
			g_pathFinding.GetNavigationMesh().SetSkinModel(&dynamic_cast<StaticMapObject*>(mapChip)->GetSkinModel());
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
			//�}�b�v�`�b�v�𐶐�
			mapChip->Init(mInfo.m_position, mInfo.m_rotation, mInfo.m_modelName);
			m_mapChip.push_back(mapChip);

			//�}�b�v�`�b�v�Ɏ��g�̃C�e���[�^�[�ƃ}�b�v�̃C���X�^���X��n��(�폜�̎��Ɏg��)
			std::list<MapChip*>::iterator iterator = m_mapChip.end();
			iterator--;
			mapChip->SetIterator(this, iterator);
		}
	}

	for (IEnemy* enemy : m_enemyList) 
	{
		//��������O���[�v�����߂�
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
}


void Map::MapChipErase(std::list<MapChip*>::iterator iterator)
{
	Delete(*iterator);
	iterator = m_mapChip.erase(iterator);
}

void Map::SetIsMapChipActive(bool isActive)
{

	//�G�̃A�N�e�B�u�ݒ�
	for (auto& enemy : m_enemyList)
	{
		enemy->SetIsActive(isActive);

	}
	//�G�O���[�v�N���X�̃A�N�e�B�u�ݒ�
	for (auto& enemyGroup : m_enemyGroupList)
	{
		enemyGroup->SetIsActive(isActive);
	}
	for (auto& shop : m_shopManager->Getlist())
	{
		shop->SetIsActive(isActive);
	}
	//�{�X�̓����̐ݒ�
	if (&GetMaw())
	{
		GetMaw().SetIsActive(isActive);
	}
	//�v���C���[�̓����̐ݒ�
	if (&GetPlayer())
	{
		GetPlayer().SetIsActive(isActive);
	}
}

void Map::SetIsMapChipActiveUpdate(bool isActive)
{
	//�G�̃A�N�e�B�u�ݒ�
	for (auto& enemy : m_enemyList)
	{
		enemy->SetIsActiveUpdate(isActive);

	}
	//�G�O���[�v�N���X�̃A�N�e�B�u�ݒ�
	for (auto& enemyGroup : m_enemyGroupList)
	{
		enemyGroup->SetIsActiveUpdate(isActive);
	}
	for (auto& shop : m_shopManager->Getlist())
	{
		shop->SetIsActiveUpdate(isActive);
	}
	//�{�X�̓����̐ݒ�
	if (&GetMaw())
	{
		GetMaw().SetIsActiveUpdate(isActive);
	}
	//�v���C���[�̓����̐ݒ�
	if (&GetPlayer())
	{
		GetPlayer().SetIsActiveUpdate(isActive);
	}
}

void Map::BeforeDead()
{
	//�{�X������Ă��Ȃ�������
	if (&GetMaw() != NULL)
	{
		GetMaw().Destroy();
	}
	//�}�b�v�`�b�v�̏���
	for (MapChip* mapchip : m_mapChip)
	{
		Delete(mapchip);
	}
	m_mapChip.clear();

	//NPC�̏���
	m_shopManager->DeleteList();
	Delete(m_shopManager);

	//�G�l�~�[�O���[�v�̏���
	for (CEnemyGroup* enemygroup : m_enemyGroupList)
	{
		Delete(enemygroup);
	}
	m_enemyGroupList.clear();

	//�G�l�~�[�̏���
	for (IEnemy* enemy : m_enemyList)
	{
		Delete(enemy);
	}
	m_enemyList.clear();

	if (&GetPlayer() != nullptr) 
	{
		//�v���C���[�̏���
		GetPlayer().Destroy();
	}
	Delete(&Sky());

}