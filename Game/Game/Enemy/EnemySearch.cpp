#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

void CEnemySearch::Update()
{
	if (&GetPlayer() == nullptr)
	{
		return;
	}
	std::list<SEnemyGroupData> groupList = m_enemy->GetEnemyGroup()->GetGroupList();
	
	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyGroupPosition = m_enemy->GetEnemyGroup()->GetPosition();
	CVector3 distance = playerPos - enemyGroupPosition;
	float length = distance.Length();

}
