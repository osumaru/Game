#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

void CEnemySearch::Update()
{
	std::list<SEnemyGroupData> groupList = m_enemy->GetEnemyGroup()->GetGroupList();

	//プレイヤーとの距離を計算
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyGroupPosition = m_enemy->GetEnemyGroup()->GetPosition();
	CVector3 distance = playerPos - enemyGroupPosition;
	float length = distance.Length();

	bool isFind = false;
	if (length < 20.0f || m_enemy->GetIsDamage() || m_enemy->IsWireHit()) 
	{
		//プレイヤーを見つけた
		isFind = true;
	}
	for (auto& enemyData : groupList)
	{
		//グループ全員に通知
		enemyData.enemy->SetIsFind(isFind);
	}
}
