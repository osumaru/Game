#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//�ړ����Ȃ�
	CVector3 moveSpeed = CVector3::Zero;
	m_enemy->SetMoveSpeed(moveSpeed);

	//�U���A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enAnimation_Attack);

	m_enemy->Attack();

	return true;
}

void CEnemyAttack::Update()
{
	//�v���C���[���_���[�W���󂯂Ă��Ȃ�
	if (!GetPlayer().GetIsDamage()) {
		//��̃{�[���̃��[���h�s����擾
		CMatrix leftHandMatrix = m_enemy->GetBoneWorldMatrix(L"LeftHand");
		CVector3 leftHandPosition;
		leftHandPosition.x = leftHandMatrix.m[3][0];
		leftHandPosition.y = leftHandMatrix.m[3][1];
		leftHandPosition.z = leftHandMatrix.m[3][2];

		//�v���C���[�Ƃ̋������v�Z
		CVector3 playerPosition = GetPlayer().GetPosition();
		CVector3 distance = playerPosition - m_enemy->GetPosition();
		distance.y = 0.0f;
		{
			//�G�̍U���Ƃ̋������v�Z
			playerPosition.y += 2.5f;
			CVector3 distance = leftHandPosition - playerPosition;
			float length = distance.Length();
			if (length < 1.5f) {
				//�v���C���[���_���[�W���󂯂�
				GetPlayer().SetDamage(m_enemy->GetStatus().strength);
				GetPlayer().SetDamageEnemyPos(m_enemy->GetPosition());
			}
		}
	}

	if (m_enemy->IsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		m_esm->ChangeState(CEnemyState::enState_AttackWait);
	}
}