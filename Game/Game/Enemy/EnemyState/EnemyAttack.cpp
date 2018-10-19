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
	float length = 0.0f;
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

	CMatrix enemyWorldMatrix = m_enemy->GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	toPlayerPos.y = 0.0f;
	toPlayerPos.Normalize();
	float angle = enemyForward.Dot(toPlayerPos);
	angle = acosf(angle);

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
		else if (fabsf(angle) < CMath::DegToRad(20.0f) && length < 2.0f) {
			m_enemy->PlayAnimation(CEnemyState::enState_Attack);
		}
		else {
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
	}
}
