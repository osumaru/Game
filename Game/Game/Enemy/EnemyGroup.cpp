#include "stdafx.h"
#include "EnemyGroup.h"
#include "IEnemy.h"
#include "Ninja.h"
#include "Zombie.h"
#include "Samurai.h"
#include "Warrok/Warrok.h"
#include "../Scene/SceneManager.h"

void CEnemyGroup::Update()
{


	//グループ全員がいなくなったらリスポーン
	if (m_groupNum <= 0 && !m_respawnDataList.empty() && !GetSceneManager().GetSceneChange())
	{
		m_timer += GameTime().GetDeltaFrameTime();
		if (m_timer > RESPAWN_TIME)
		{
			m_timer = 0.0f;

			for (auto& respawnData : m_respawnDataList)
			{
				//リスポーンエフェクトの初期化
				CEffect respawnEffect;
				respawnEffect.Init(L"Assets/Effect/respawnEffect.efk");
				respawnEffect.SetScale({ 1.0f,1.0f,1.0f });
				respawnEffect.SetPosition(respawnData.m_position);
				respawnEffect.Play();
				respawnEffect.Update();
				//エネミーの初期化
				GetSceneManager().GetMap()->CreateMapChip(respawnData);
			}
			m_respawnDataList.clear();
		}
	}
}

void CEnemyGroup::Add(const SMapChipInfo& info)
{
	m_groupNum++;
	m_respawnDataList.push_back(info);
}
