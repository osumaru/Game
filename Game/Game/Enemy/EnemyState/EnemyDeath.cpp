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
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Death, 0.3f);

	//�ړ����Ȃ�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 speed = CVector3::Zero;
	moveSpeed.x = speed.x;
	moveSpeed.z = speed.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//�v���C���[���o���l�l��
	GetPlayer().ExpUP(m_enemy->GetStatus().exp);

	m_enemy->SetIsDead(true);

	return true;
}

void CEnemyDeath::Update()
{
	//���S�A�j���[�V�������I�������񕜃A�C�e���Ƃ����A�󔠂��o��
	if (!m_enemy->GetAnimation().IsPlay()) {
		//����
		CMoney* money = New<CMoney>(PRIORITY_ITEM);
		money->Init(m_enemy->GetStatus().gold);
		money->Pop(m_enemy->GetPosition());
		//�����_����0�`9�̐��l���擾
		int randomNum = Random().GetRandSInt() % 10;
		//�T���̊m���ŏo��
		if (randomNum < 5)
		{
			//�񕜃A�C�e��
			CRecoveryItem* recoveryItem = New<CRecoveryItem>(PRIORITY_ITEM);
			recoveryItem->Init();
			recoveryItem->Pop(m_enemy->GetPosition());
		}
		//�R���̊m���ŏo��
		if (randomNum < 3) 
		{
			//��
			CTreasureChest* treasureChest = New<CTreasureChest>(PRIORITY_ITEM);
			treasureChest->Init(m_enemy->GetPosition());
		}
		m_enemy->EnemyListErase();
		Delete(m_enemy);
	}
}
