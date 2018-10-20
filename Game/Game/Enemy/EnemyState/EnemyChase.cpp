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
	if (m_enemy->IsWireHit()) {
		//���C���[���������Ă����牽�����Ȃ�
		return;
	}

	//�v���C���[��ǂ�������
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerDir = playerPos - m_enemy->GetPosition();
	float length = toPlayerDir.Length();

	CMatrix enemyWorldMatrix = m_enemy->GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	toPlayerPos.y = 0.0f;
	toPlayerPos.Normalize();
	float angle = enemyForward.Dot(toPlayerPos);
	angle = acosf(angle);

	if (m_enemy->IsDamage()){
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (fabsf(angle) < CMath::DegToRad(30.0f) && length < 2.0f) {
		//�v���C���[�Ƌ������߂�
		m_esm->ChangeState(CEnemyState::enState_Attack);
	}
	if (length > 15.0f) {
		//�v���C���[�����ꂽ��߂��Ă���
		m_esm->ChangeState(CEnemyState::enState_Walk);
	}
}
