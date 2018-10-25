#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"

bool CEnemyDamage::Start()
{
	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Damage);

	//�_���[�W�v�Z
	int playerStrength = GetPlayer().GetStatus().Strength;
	int enemyDefence = m_enemy->GetStatus().Defense;
	int damage = playerStrength - enemyDefence;
	m_enemy->HpDamage(damage);

	return true;
}

void CEnemyDamage::Update()
{
	//�_���[�W�v�Z
	int playerStrength = GetPlayer().GetStatus().Strength;
	int enemyDefence = m_enemy->GetStatus().Defense;
	int damage = playerStrength - enemyDefence;

	CMatrix leftShoulderMatrix = m_enemy->GetBoneWorldMatrix(L"LeftShoulder");
	CVector3 leftShoulderPos;
	leftShoulderPos.x = leftShoulderMatrix.m[3][0];
	leftShoulderPos.y = leftShoulderMatrix.m[3][1];
	leftShoulderPos.z = leftShoulderMatrix.m[3][2];
	CMatrix viewMatrix = GetGameCamera().GetViewMatrix();
	CMatrix projectionMatrix = GetGameCamera().GetProjectionMatrix();
	//�r���[�ϊ�
	CVector4 viewPosition = leftShoulderPos;
	viewMatrix.Mul(viewPosition);
	//�v���W�F�N�V�����ϊ�
	CVector4 projectionPosition = viewPosition;
	projectionMatrix.Mul(projectionPosition);
	projectionPosition = projectionPosition / projectionPosition.w;
	//�X�N���[���ϊ�
	CVector2 screenPosition;
	screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * FrameBufferWidth() - (FrameBufferWidth() / 2.0f);
	screenPosition.y = (1.0f + projectionPosition.y) / 2.0f * FrameBufferHeight() - (FrameBufferHeight() / 2.0f);

	m_enemy->DamageCaluc(damage);
	m_enemy->SetDamageCalucPos(screenPosition);

	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();

	CMatrix enemyWorldMatrix = m_enemy->GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();
	toPlayerPos.y = 0.0f;
	toPlayerPos.Normalize();
	float angle = enemyForward.Dot(toPlayerPos);
	angle = acosf(angle);

	if (!m_enemy->IsPlayAnimation()) {
		//�A�j���[�V�������I�����Ă���
		if (fabsf(angle) < CMath::DegToRad(20.0f) && length < 2.0f) {
			//�߂���΍U��
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
		else if (m_enemy->IsFind()) {
			//��������Ă�����v���C���[��ǂ�������
			m_esm->ChangeState(CEnemyState::enState_Chase);
		}
		else {
			//������Ε����n�߂�
			m_esm->ChangeState(CEnemyState::enState_Walk);
		}
		//�_���[�W�\������߂�
		m_enemy->DamageIndicateReset();
		//�_���[�W���󂯂��t���O��߂�
		m_enemy->SetIsDamage(false);
	}
	if (m_enemy->GetStatus().Hp <= 0) {
		//HP�������Ȃ�Ύ��S
		m_esm->ChangeState(CEnemyState::enState_Death);
		//�_���[�W�\������߂�
		m_enemy->DamageIndicateReset();
		//�_���[�W���󂯂��t���O��߂�
		m_enemy->SetIsDamage(false);
	}
}
