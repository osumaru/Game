#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

void CEnemySearch::Update()
{
	if (&m_enemy->GetEnemyGroup()->GetGroupList() == NULL) { return; }
	std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();

	//プレイヤーとの距離を計算
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyGroupPosition = m_enemy->GetEnemyGroup()->GetPosition();
	CVector3 distance = playerPos - enemyGroupPosition;
	float length = distance.Length();
	////視野内にプレイヤーがいるか判定
	//bool isFindPlayer = m_enemy->CalucFanShape(45.0f, playerPos);

	bool isFind = false;
	if (/*isFindPlayer &&*/ length < 20.0f || m_enemy->IsDamage() || m_enemy->IsWireHit()) {
		////プレイヤーを発見した又はダメージを受けた
		//for (auto& enemy : groupList) 
		//{
		//	//グループ全員に通知
		//	enemy->SetIsFind(true);
		//}
		isFind = true;
	}
	for (auto& enemy : groupList)
	{
		enemy->SetIsFind(isFind);
	}
	//	//所属するグループのリストを取得
	//	if (&m_enemy->GetEnemyGroup()->GetGroupList() == NULL) { return; }
	//	std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();
	//	std::list<float> lengthList;

	//	for (auto& enemy : groupList) 
	//	{
	//		//グループ全員とプレイヤーの距離を計算
	//		CVector3 enemyPos = enemy->GetPosition();
	//		CVector3 toPlayerPos = GetPlayer().GetPosition() - enemyPos;
	//		float length = toPlayerPos.Length();
	//		lengthList.push_back(length);
	//	}

	//	bool isFar = false;
	//	//グループ全員がプレイヤーから遠いか判定
	//	for (float& len : lengthList)
	//	{
	//		if (len > 8.0f) {
	//			isFar = true;
	//		}
	//		else {
	//			//グループの一人でも近ければそのまま
	//			isFar = false;
	//			break;
	//		}
	//	}

	//	if (isFar) {
	//		//グループ全員がプレイヤーから遠い
	//		for (auto& enemy : groupList)
	//		{
	//			//グループ全員に通知
	//			enemy->SetIsFind(false);
	//		}
	//	}
	//}
}
