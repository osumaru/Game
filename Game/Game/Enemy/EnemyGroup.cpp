#include "stdafx.h"
#include "EnemyGroup.h"
#include "IEnemy.h"

void CEnemyGroup::Update()
{
	std::list<IEnemy*>::iterator it;
	it = m_enemyGroupList.begin();

	while (it != m_enemyGroupList.end()) {
		if ((*it)->IsDelete()) {
			IEnemy* enemy = *it;
			it = m_enemyGroupList.erase(it);
		}
		else {
			it++;
		}
	}
}
