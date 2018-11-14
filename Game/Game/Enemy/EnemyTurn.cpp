#include "stdafx.h"
#include "EnemyTurn.h"
#include "IEnemy.h"
#include "../Player/Player.h"

void CEnemyTurn::Update()
{
	//���[���h�s�񂩂烂�f���̑O�������擾
	CMatrix worldMatrix = m_enemy->GetWorldMatrix();
	CVector3 forwardXZ;
	forwardXZ.x = worldMatrix.m[2][0];
	forwardXZ.y = 0.0f;
	forwardXZ.z = worldMatrix.m[2][2];
	forwardXZ.Normalize();

	//�ړ����x���擾
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.y = 0.0f;
	if (moveSpeed.LengthSq() < 0.01f || !m_enemy->IsDamagePossible()) {
		//�ړ����Ă��Ȃ��Ɗp�x�̌v�Z���ł��Ȃ��̂ŕԂ�
		return;
	}

	//�p�x�̌v�Z
	float targetAngle = atan2f(moveSpeed.x, moveSpeed.z);
	float currentAngle = atan2f(forwardXZ.x, forwardXZ.z);
	
	float diff = targetAngle - currentAngle;
	float a_diff = fabsf(diff);
	if (a_diff > CMath::PI) {
		//180���𒴂��Ă���̂ŁA-180.0f�`180.0f�ɕϊ�����
		diff = (CMath::PI2 - a_diff) * (a_diff / -diff);
		a_diff = fabsf(diff);
	}
	float rotSpeed = 8.0f * GameTime().GetDeltaFrameTime();
	float addAngle = 0.0f;
	if (a_diff > rotSpeed) {
		addAngle = (diff / a_diff) * rotSpeed;
	}
	else {
		addAngle = diff;
	}

	CQuaternion addRot;
	addRot.SetRotation(CVector3::AxisY, addAngle);

	CQuaternion rot = m_enemy->GetRotation();
	rot.Multiply(rot, addRot);
	m_enemy->SetRotation(rot);
}
