#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Item/RecoveryItem.h"
#include "../../Item/Money.h"
#include "../../Item/TreasureChest.h"
#include "../../Player/Player.h"

bool CEnemyDeath::Start()
{
	//死亡アニメーションを再生
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Death, 0.3f);

	//移動しない
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 speed = CVector3::Zero;
	moveSpeed.x = speed.x;
	moveSpeed.z = speed.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//プレイヤーが経験値獲得
	GetPlayer().ExpUP(m_enemy->GetStatus().exp);

	//エネミーの剛体を削除
	m_enemy->RemovedRegidBody();

	return true;
}

void CEnemyDeath::Update()
{
	//死亡アニメーションが終わったら回復アイテムとお金、宝箱を出す
	if (!m_enemy->GetAnimation().IsPlay()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(PRIORITY_ITEM);
		recoveryItem->Init();
		recoveryItem->Pop(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(PRIORITY_ITEM);
		money->Init(m_enemy->GetStatus().gold);
		money->Pop(m_enemy->GetPosition());
		CTreasureChest* treasureChest = New<CTreasureChest>(PRIORITY_ITEM);
		treasureChest->Init(m_enemy->GetPosition());
		m_enemy->StateMachineRelease();
		m_enemy->EnemyListErase();
		Delete(m_enemy);
	}
}
