#include "stdafx.h"
#include "PlayerDamage.h"
#include "../Player.h"



void CPlayerDamage::Init()
{
	//�U�����󂯂������ɉ�]������
	Rotation();
	if (!m_pPlayerGetter->GetCharacterController().IsOnGround())
	{
		//�󒆂Ń_���[�W���󂯂��琁����΂����
		m_airDamageVec = m_pPlayer->GetPosition() - m_pPlayerGetter->GetDamageEnemyPos();
		m_airDamageVec.Normalize();
		m_airDamageVec *= -4.0f;
		CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
		moveSpeed.x = m_airDamageVec.x;
		moveSpeed.z = m_airDamageVec.z;
		m_pPlayerGetter->SetMoveSpeed(m_airDamageVec);
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDamageAir, 0.1f);
		m_isSky = true;
	}
	else {
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDamage, 0.1f);
		m_isSky = false;
	}
}

void CPlayerDamage::Update()
{
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
	if (m_pPlayerGetter->GetCharacterController().IsOnGround())
	{
		CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		m_pPlayerGetter->SetMoveSpeed(moveSpeed);
		if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDown))
		{
			m_pPlayerGetter->DamageStateReset();
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDown);
		}
	}
	
	if (!m_pPlayerGetter->GetAnimation().IsPlay()&&!m_isSky)
	{
		m_pPlayerGetter->DamageStateReset();
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}

void CPlayerDamage::Rotation()
{
	//�v���C���[�̍��W����_���[�W��^�����G�l�~�[�̍��W�ւ̃x�N�g�����v�Z
	CVector3 enemyPos = m_pPlayerGetter->GetDamageEnemyPos();
	CVector3 toEnemyPos = enemyPos - m_pPlayer->GetPosition();
	toEnemyPos.Normalize();

	CMatrix playerWorldMatrix = m_pPlayer->GetSkinmodel().GetWorldMatrix();
	//�v���C���[�̑O�������擾
	CVector3 playerForward;
	playerForward.x = playerWorldMatrix.m[2][0];
	playerForward.y = playerWorldMatrix.m[2][1];
	playerForward.z = playerWorldMatrix.m[2][2];
	playerForward.Normalize();

	float angle = playerForward.Dot(toEnemyPos);
	if (angle > 1.0f) {
		angle = 1.0f;
	}
	else if (angle < -1.0f) {
		angle = -1.0f;
	}
	angle = acosf(angle);

	CVector3 Cross = playerForward;
	Cross.Cross(toEnemyPos);
	if (Cross.y < 0.0f) {
		angle *= -1.0f;
	}
	//�v���C���[����]������
	CQuaternion playerRotation = m_pPlayerGetter->GetRotation();
	CQuaternion rotation;
	rotation.SetRotation(CVector3::AxisY, angle);
	playerRotation.Multiply(rotation);
	m_pPlayerGetter->SetRotation(playerRotation);
}
