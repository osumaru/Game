#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

void CEnemySearch::Update()
{
	std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();

	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyGroupPosition = m_enemy->GetEnemyGroup()->GetPosition();
	CVector3 distance = playerPos - enemyGroupPosition;
	float length = distance.Length();

	bool isFind = false;
	if (length < 20.0f || m_enemy->GetIsDamage() || m_enemy->IsWireHit()) 
	{
		//�v���C���[��������
		isFind = true;
	}
	for (auto& enemy : groupList)
	{
		//�O���[�v�S���ɒʒm
		enemy->SetIsFind(isFind);
	}
}
