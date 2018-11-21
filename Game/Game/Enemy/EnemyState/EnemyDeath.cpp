#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Item/RecoveryItem.h"
#include "../../Item/Money.h"
#include "../../Item/TreasureChest.h"
#include "../../Player/Player.h"

bool CEnemyDeath::Start()
{
	//���S�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Death);

	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 speed = CVector3::Zero;
	moveSpeed.x = speed.x;
	moveSpeed.z = speed.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//�v���C���[���o���l�l��
	GetPlayer().ExpUP(m_enemy->GetStatus().Exp);

	return true;
}

void CEnemyDeath::Update()
{
	//���S�A�j���[�V�������I�������񕜃A�C�e���Ƃ������o��
	if (!m_enemy->IsPlayAnimation()) {
		CRecoveryItem* recoveryItem = New<CRecoveryItem>(PRIORITY_ITEM);
		recoveryItem->Pop(m_enemy->GetPosition());
		CMoney* money = New<CMoney>(PRIORITY_ITEM);
		money->Pop(m_enemy->GetPosition());
		money->SetGold(m_enemy->GetStatus().Gold);
		CTreasureChest* treasureChest = New<CTreasureChest>(PRIORITY_ITEM);
		treasureChest->Init(m_enemy->GetPosition());
		m_enemy->StateMachineRelease();
		m_enemy->EnemyListErase();
		Delete(m_enemy);
	}
}
