#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../../UI/DamageNumber/DamageNumber.h"

void CEnemyDamage::Init()
{
	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enAnimation_Damage);

	//�_���[�W���l��������
	m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
	m_damageNumber->Init(m_enemy);

	//�_���[�W���󂯂��t���O��߂�
	m_enemy->SetIsDamage(false);

	m_friction = 0.5f;
	//m_debugDamageCount++;
}

bool CEnemyDamage::Start()
{
	//������
	Init();

	return true;
}

void CEnemyDamage::Update()
{
	//�m�b�N�o�b�N������
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 knockBack = m_enemy->GetPosition() - GetPlayer().GetPosition();
	knockBack.y = 0.0f;
	knockBack.Normalize();
	if (m_friction >= m_knockBackSpeed) {
		m_friction = m_knockBackSpeed;
	}
	knockBack *= m_knockBackSpeed - m_friction;
	m_friction += m_friction;
	moveSpeed.x = knockBack.x;
	moveSpeed.z = knockBack.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//�v���C���[�Ƃ̋������v�Z����
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();
	//�U���͈͂ɂ��邩�ǂ�������
	bool isRange = m_enemy->CalucFanShape(10.0f, playerPos);

	if (m_enemy->GetStatus().hp <= 0) {
		//HP�������Ȃ�Ύ��S
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
	else if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		//if (m_debugDamageCount >= 2) {
		//	m_debugDamageCount = 0;
		//	//�X�^������U�����󂯂�
		//	m_esm->ChangeState(CEnemyState::enState_Stan);
		//}
		if (isRange && length < 1.2f) {
			//�߂���΍U��
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else {
			//�v���C���[��ǂ�������
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
	}
	else if(m_enemy->IsDamage()) {
		//������x�_���[�W���󂯂��珉����
		Init();
	}
}

void CEnemyDamage::Release()
{
	if (m_damageNumber != nullptr) {
		Delete(m_damageNumber);
		m_damageNumber = nullptr;
	}
}
