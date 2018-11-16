#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../../UI/DamageNumber/DamageNumber.h"

void CEnemyDamage::Init()
{
	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	m_damageNumber = New<CDamageNumber>(0);
	m_damageNumber->Init(m_enemy);
	debugNum++;

	//�_���[�W���󂯂��t���O��߂�
	m_enemy->SetIsDamage(false);

	//�m�b�N�o�b�N������
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	m_knockBack = m_enemy->GetPosition() - GetPlayer().GetPosition();
	m_knockBack.y = 0.0f;
	m_knockBack.Normalize();
	m_knockBack *= m_knockBackSpeed;
	moveSpeed.x = m_knockBack.x;
	moveSpeed.z = m_knockBack.z;
	m_enemy->SetMoveSpeed(moveSpeed);
	m_enemy->SetMoveSpeed(CVector3::Zero);
}

bool CEnemyDamage::Start()
{
	//������
	Init();

	return true;
}

void CEnemyDamage::Update()
{
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 knockBack = moveSpeed;
	knockBack *= GameTime().GetDeltaFrameTime() * 3.0f;
	moveSpeed -= knockBack;
	//m_enemy->SetMoveSpeed(moveSpeed);

	//�v���C���[�Ƃ̋������v�Z����
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();
	//���͈̔͂ɂ��邩�ǂ�������
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (m_enemy->GetStatus().Hp <= 0) {
		//HP�������Ȃ�Ύ��S
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
	else if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		if (isRange  && length < 2.0f) {
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
		debugNum--;
		Delete(m_damageNumber);
		m_damageNumber = nullptr;
	}
}
