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
	//float length = 0.0f;
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
		//length = distance.Length();
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

	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 distance = playerPos - m_enemy->GetPosition();
	distance.y = 0.0f;
	float length = distance.Length();
	//���͈̔͂ɓ����Ă��邩
	bool isRange = m_enemy->CalucFanShape(20.0f, playerPos);

	if (m_enemy->IsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage); 
	}
	if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		if (!m_enemy->IsFind()) {
			//�v���C���[��������ɂ��Ȃ�
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		else if (isRange && length < 1.2f) {
			m_enemy->PlayAnimation(CEnemyState::enState_Attack);
		}
		else {
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
	}
}
