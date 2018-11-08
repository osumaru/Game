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
	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	float length = toPlayerDir.Length();

	//���͈̔͂ɓ����Ă��邩
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (m_enemy->IsDamage()){
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (isRange && length < 1.2f) {
		//�v���C���[�Ƌ������߂����U���͈͂ɂ���
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (!m_enemy->IsFind()) {
		//�v���C���[�����ꂽ��߂��Ă���
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}
