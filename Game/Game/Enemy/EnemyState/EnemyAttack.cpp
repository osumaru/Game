#include "stdafx.h"
#include "EnemyAttack.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttack::Start()
{
	//�U���A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Attack);

	//�U������Ƃ��͈ړ�����߂�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

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
		length = distance.Length();
		{
			//�G�̍U���Ƃ̋������v�Z
			playerPosition.y += 2.5f;
			CVector3 distance = leftHandPosition - playerPosition;
			float length = distance.Length();
			if (length < 1.5f) {
				//�v���C���[���_���[�W���󂯂�
				GetPlayer().GetDamage();
			}
		}
	}

	if (m_enemy->IsDamage()) {
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		if (!m_enemy->IsFind()) {
			//�v���C���[��������ɂ��Ȃ�
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		else if (m_enemy->IsFind() && length > 2.0f) {
			//�v���C���[��������ɂ��銎�����������Ȃ�߂Â�
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		else {
			//������x�U��������
			m_enemy->PlayAnimation(CEnemyState::enState_Attack);
		}
	}
}
