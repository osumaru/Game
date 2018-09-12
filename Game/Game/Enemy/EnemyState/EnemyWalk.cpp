#include "stdafx.h"
#include "EnemyWalk.h"
#include "../IEnemy.h"

bool EnemyWalk::Start()
{
	//�����A�j���[�V�������Đ�
	m_enemy->PlayAnimation(CEnemyState::enState_Walk);

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
	m_destination = m_enemy->GetInitPosition() + toRandomPosition;

	//�ړ����x���v�Z
	toRandomPosition.Normalize();
	toRandomPosition *= m_speed;
	m_enemy->SetMoveSpeed(toRandomPosition);

	return true;
}

void EnemyWalk::Update()
{
	bool isMoveFinish = false;
	//�ړ����x���擾
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	//���݂̍��W����ړ���܂ł̋������v�Z
	CVector3 position = m_enemy->GetPosition();
	CVector3 distance = m_destination - position;
	float length = distance.Length();
	if (length > 0.3f) {
		//�߂��Ȃ���΂��̂܂ܐi��
		distance.Normalize();
		distance *= m_speed;
		moveSpeed.x = distance.x;
		moveSpeed.z = distance.z;
	}
	else {
		isMoveFinish = true;
	}
	//�ړ����x��ݒ�
	m_enemy->SetMoveSpeed(moveSpeed);

	//�ړ���܂ňړ�������~�܂�
	if (isMoveFinish) {
		m_esm->ChangeState(CEnemyState::enState_Idle);
	}
}
