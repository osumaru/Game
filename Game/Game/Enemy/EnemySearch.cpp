#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

void CEnemySearch::Update()
{
	//プレイヤーとの距離を計算
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 distance = playerPos - m_enemy->GetPosition();
	float length = distance.Length();
	//視野内にプレイヤーがいるか判定
	bool isFindPlayer = m_enemy->CalucFanShape(45.0f, playerPos);

	if (isFindPlayer && length < 15.0f || m_enemy->IsDamage() || m_enemy->IsWireHit()) {
		//プレイヤーを発見した又はダメージを受けた
		std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();
		for (auto& enemy : groupList) 
		{
			//グループ全員に通知
			enemy->SetIsFind(true);
		}
	}
	else {
		//所属するグループのリストを取得
		if (&m_enemy->GetEnemyGroup()->GetGroupList() == NULL) { return; }
		std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();
		std::list<float> lengthList;

		for (auto& enemy : groupList) 
		{
			//グループ全員とプレイヤーの距離を計算
			CVector3 enemyPos = enemy->GetPosition();
			CVector3 toPlayerPos = GetPlayer().GetPosition() - enemyPos;
			float length = toPlayerPos.Length();
			lengthList.push_back(length);
		}

		bool isFar = false;
		//グループ全員がプレイヤーから遠いか判定
		for (float& len : lengthList)
		{
			if (len > 8.0f) {
				isFar = true;
			}
			else {
				//グループの一人でも近ければそのまま
				isFar = false;
				break;
			}
		}

		if (isFar) {
			//グループ全員がプレイヤーから遠い
			for (auto& enemy : groupList)
			{
				//グループ全員に通知
				enemy->SetIsFind(false);
			}
		}
	}
}
