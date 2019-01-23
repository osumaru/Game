#include "stdafx.h"
#include "EnemyGroup.h"
#include "IEnemy.h"

void CEnemyGroup::Update()
{
	std::list<SEnemyGroupData>::iterator it;
	it = m_enemyGroupList.begin();

	while (it != m_enemyGroupList.end()) 
	{
		//エネミーが死亡していたらグループリストから外す
		if ((*it).enemy->GetIsDead()) 
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
}
