#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"
#include "../EnemyGroup.h"

bool CEnemyWalk::Start()
{
	//�����A�j���[�V�������Đ�
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Walk, 0.3f);

	//�����_���Ɉړ��������
	float randomPositionX = (float)Random().GetRandDouble();
	float randomPositionZ = (float)Random().GetRandDouble();
	//0.0�`20.0�̒l�ɕϊ�
	randomPositionX *= 20.0f;
	randomPositionZ *= 20.0f;
	//-10.0�`10.0�̒l�ɕϊ�
	randomPositionX -= 10.0f;
	randomPositionZ -= 10.0f;
	//�ړ���̃x�N�g�����v�Z
	CVector3 toRandomPosition;
	toRandomPosition.x = randomPositionX;
	toRandomPosition.y = 0.0f;
	toRandomPosition.z = randomPositionZ;

	//�ړ���̍��W��ۑ�
	m_destination = m_enemy->GetEnemyGroup()->GetPosition() + toRandomPosition;

	m_isMoveEnd = false;
	return true;
}

void CEnemyWalk::Update()
{
	//�ړ�
	Move();

	if (m_enemy->GetIsDamage()) {
		//�_���[�W���󂯂�
		m_esm->ChangeState(CEnemyState::enState_Damage);
	}
	if (m_isMoveEnd) {
		//�ړ���܂ňړ�������~�܂�
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
	if (m_enemy->IsFind()) {
		//�v���C���[��������ɂ���
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
}

void CEnemyWalk::Move()
{
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	float speed = 2.0f;

	CVector3 position = m_enemy->GetPosition();
	CVector3 distance = m_destination - position;
	distance.y = 0.0f;
	if (distance.Length() > 0.3f)
	{
		//�ړ���Ɉړ�����
		distance.Normalize();
		distance *= speed;
		moveSpeed.x = distance.x;
		moveSpeed.z = distance.z;
	}
	else
	{
		//�ړ���ɒ�����
		m_isMoveEnd = true;
	}

	m_enemy->SetMoveSpeed(moveSpeed);
}
