#include "stdafx.h"
#include "EnemyGroup.h"
#include "IEnemy.h"

void CEnemyGroup::Update()
{
	std::list<SEnemyGroupData>::iterator it;
	it = m_enemyGroupList.begin();

	while (it != m_enemyGroupList.end()) 
	{
		//�G�l�~�[�����S���Ă�����O���[�v���X�g����O��
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
	//�O���[�v���̃G�l�~�[�ԍ����X�V����
	while (it != m_enemyGroupList.end()) 
	{
		groupNum++;
		(*it).groupNumber = groupNum;
		it++;
	}
	m_groupNum = groupNum;
}
