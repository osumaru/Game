#include "stdafx.h"
#include "EnemyGroup.h"
#include "IEnemy.h"
#include "Ninja.h"
#include "Zombie.h"
#include "Samurai.h"
#include "Warrok/Warrok.h"
#include "../Map/Map.h"
#include "../Scene/SceneManager.h"

void CEnemyGroup::Update()
{
	std::list<SEnemyGroupData>::iterator it;
	it = m_enemyGroupList.begin();

	while (it != m_enemyGroupList.end()) 
	{
		//エネミーが死亡していたらグループリストから外す
		const CEnemyDeath* enemyDeath = dynamic_cast<const CEnemyDeath*>((*it).enemy->GetStateMachine().GetState(CEnemyState::enState_Death));
		if (enemyDeath->GetIsAnimationEnd())
		{
			it = m_enemyGroupList.erase(it);
		}
		else
		{
			it++;
		}
	}

	it = m_enemyGroupList.begin();
	int groupNum = 0;
	//グループ内のエネミー番号を更新する
	while (it != m_enemyGroupList.end()) 
	{
		groupNum++;
		(*it).groupNumber = groupNum;
		it++;
	}
	m_groupNum = groupNum;

	if (m_enemyGroupList.empty() && !GetSceneManager().GetSceneChange())
	{
		m_timer += GameTime().GetDeltaFrameTime();
		if (m_timer > RESPAWN_TIME)
		{
			m_timer = 0.0f;
			for (auto& respawnData : m_respawnDataList)
			{
				std::list<IEnemy*>::iterator it;
				IEnemy* enemy = nullptr;
				switch (respawnData.enemyType)
				{
				case enEnemy_Ninja:
					enemy = New<CNinja>(PRIORITY_ENEMY);
					break;
				case enEnemy_Samurai:
					enemy = New<CSamurai>(PRIORITY_ENEMY);
					break;
				case enEnemy_Warrok:
					enemy = New<CWarrok>(PRIORITY_ENEMY);
					break;
				case enEnemy_Zombi:
					enemy = New<CZombie>(PRIORITY_ENEMY);
					break;
				}
				enemy->Init(respawnData.initPosition, respawnData.level);
				GetSceneManager().GetMap()->GetEnemyList().push_back(enemy);
				it = GetSceneManager().GetMap()->GetEnemyList().end();
				it--;
				enemy->SetIterater(it);
				enemy->SetEnemyGroup(this);
				m_groupNum++;
				m_enemyGroupList.push_back({ enemy, m_groupNum });
				enemy->AddObject();
			}
		}
	}
}

void CEnemyGroup::Add(IEnemy * enemy)
{
	m_groupNum++;
	m_enemyGroupList.push_back({ enemy, m_groupNum });
	m_respawnDataList.push_back({ enemy->GetPosition(),  enemy->GetEnemyType(), enemy->GetStatus().level});
}
