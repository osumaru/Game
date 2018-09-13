#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//�U���A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Attack);
	return true;
}

void CEnemyAttack::Update()
{
	//��̃{�[���̃��[���h�s����擾
	CMatrix leftHandMatrix = m_enemy->GetBoneWorldMatrix(L"LeftHand");
	CVector3 leftHandPosition;
	leftHandPosition.x = leftHandMatrix.m[3][0];
	leftHandPosition.y = leftHandMatrix.m[3][1];
	leftHandPosition.z = leftHandMatrix.m[3][2];

	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPosition = GetPlayer().GetPosition();
	playerPosition.y += 2.5f;
	CVector3 distance = leftHandPosition - playerPosition;
	float length = distance.Length();
	if (length < 1.5f) {
		//�_���[�W���󂯂�
		GetPlayer().GetDamage();
		m_enemy->SetIsAttackHit(true);
	}

	if (Pad().IsTriggerButton(enButtonA)) {
		m_esm->ChangeState(CEnemyState::enState_Damage);
		m_enemy->SetIsAttackHit(false);
	}
}
