#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../EnemyGroup.h"

bool CEnemyDamage::Start()
{
	

	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	//�_���[�W�v�Z
	int playerStrength = GetPlayer().GetStatus().Strength;
	int enemyDefence = m_enemy->GetStatus().Defense;
	int damage = playerStrength - enemyDefence;
	m_enemy->HpDamage(damage);
	CVector3 enemyPos = m_enemy->GetPosition();
	m_enemy->SetDamagePos({ enemyPos.x, enemyPos.y });
	m_enemy->DamageCalculation(damage);

	return true;
}

void CEnemyDamage::Update()
{
	//�_���[�W���󂯂Ă���Ƃ��͓����Ȃ�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();

	if (!m_enemy->IsPlayAnimation()) {
		if (length < 2.0f) {
			//�߂���΍U��
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else if (m_enemy->IsFind()) {
			//�A�j���[�V�������I�����Ă���΃v���C���[��ǂ�������
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		else {
			//������Ε����n�߂�
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		//�_���[�W�\���̕`�����߂�
		m_enemy->DamageIndicateReset();
		//�_���[�W���󂯂��t���O��߂�
		m_enemy->SetIsDamage(false);
	}
	if (m_enemy->GetStatus().Hp <= 0) {
		//HP�������Ȃ�Ύ��S
		m_esm->ChangeState(CEnemyState::enState_Death);
		//�_���[�W�\���̕`�����߂�
		m_enemy->DamageIndicateReset();
	}
}
