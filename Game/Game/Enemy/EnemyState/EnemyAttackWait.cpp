#include "EnemyAttackWait.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"

bool CEnemyAttackWait::Start()
{
	m_enemy->PlayAnimation(CEnemyState::enState_Idle);
	//�^�C�}�[��������
	m_timer = 0.0f;

	return true;
}

void CEnemyAttackWait::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();
	if (m_timer <= 3.0f)
	{
		//���΂炭�������Ȃ�
		return;
	}

	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 distance = m_enemy->GetPosition() - playerPos;
	float length = distance.Length();
	if (m_enemy->IsDamage())
	{
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (length < 1.2f) 
	{
		bool isRange = m_enemy->CalucFanShape(10.0f, playerPos);
		if (!isRange) {
			//�U���͈͂ɓ����Ă��Ȃ��̂ŉ�]������
			Rotation();
		}
		else {
			//�U��
			m_esm->ChangeState(CEnemyState::enState_Attack);
		}
	}
	else 
	{
		//�ǂ�������
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}

void CEnemyAttackWait::Rotation()
{
	//�v���C���[�ւ̃x�N�g�������߂�
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 enemyPos = m_enemy->GetPosition();
	CVector3 toPlayer = playerPos - enemyPos;
	toPlayer.Normalize();
	//�G�l�~�[�̑O���������߂�
	CMatrix enemyWorldMatrix = m_enemy->GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();
	//�p�x���v�Z
	float angle = toPlayer.Dot(enemyForward);
	if (angle > 1.0f) {
		angle = 1.0f;
	}
	else if (angle < -1.0f) {
		angle = -1.0f;
	}
	angle = acosf(angle);
	//��]���������߂�
	CVector3 Cross = toPlayer;
	Cross.Cross(enemyForward);
	if (Cross.y > 0.0f) {
		angle *= -1.0f;
	}
	//���X�ɉ�]�����邽�߂ɕ���
	angle /= 5.0f;
	//�G�l�~�[����]������
	CQuaternion enemyRotation = m_enemy->GetRotation();
	CQuaternion rotation;
	rotation.SetRotation(CVector3::AxisY, angle);
	enemyRotation.Multiply(rotation);
	m_enemy->SetRotation(enemyRotation);
}
