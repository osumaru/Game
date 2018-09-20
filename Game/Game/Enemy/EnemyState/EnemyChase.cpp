#include "stdafx.h"
#include "EnemyChase.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyChase::Start()
{
	//�����A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Chase);

	return true;
}

void CEnemyChase::Update()
{
	//�ړ����x���擾
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	//�v���C���[��ǂ�������
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	float length = toPlayerDir.Length();
	toPlayerDir.Normalize();
	toPlayerDir *= m_speed;
	moveSpeed.x = toPlayerDir.x;
	moveSpeed.z = toPlayerDir.z;
	//�ړ����x��ݒ�
	m_enemy->SetMoveSpeed(moveSpeed);

	if (m_enemy->IsDamage()){
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (length < 2.0f) {
		//�v���C���[�Ƌ������߂�
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (!m_enemy->IsFind()) {
		//�v���C���[�����ꂽ��߂��Ă���
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}
