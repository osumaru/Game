#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"

void CEnemySearch::Update()
{
	//���[���h�s�񂩂烂�f���̑O�������擾
	CMatrix worldMatrix = m_enemy->GetWorldMatrix();
	CVector3 forwardXZ;
	forwardXZ.x = worldMatrix.m[2][0];
	forwardXZ.y = 0.0f;
	forwardXZ.z = worldMatrix.m[2][2];
	forwardXZ.Normalize();

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_enemy->GetPosition();
	float length = toPlayerDir.Length();
	toPlayerDir.y = 0.0f;
	toPlayerDir.Normalize();

	float angle = toPlayerDir.Dot(forwardXZ);
	angle = acosf(angle);

	if (fabsf(angle) < CMath::DegToRad(30.0f) && length < 8.0f) {
		//�v���C���[�𔭌�����
		m_enemy->SetIsFind(true);
	}
	else {
		m_enemy->SetIsFind(false);
	}
}
