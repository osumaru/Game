#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

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

	if (fabsf(angle) < CMath::DegToRad(50.0f) && length < 15.0f || m_enemy->IsDamage() || m_enemy->IsWireHit()) {
		//�v���C���[�𔭌��������̓_���[�W���󂯂�
		std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();
		for (auto& enemy : groupList) 
		{
			//�O���[�v�S���ɒʒm
			enemy->SetIsFind(true);
		}
	}
	else {
		//��������O���[�v�̃��X�g���擾
		std::list<IEnemy*> groupList = m_enemy->GetEnemyGroup()->GetGroupList();
		std::list<float> lengthList;

		for (auto& enemy : groupList) 
		{
			//�O���[�v�S���ƃv���C���[�̋������v�Z
			CVector3 enemyPos = enemy->GetPosition();
			CVector3 toPlayerPos = GetPlayer().GetPosition() - enemyPos;
			float length = toPlayerPos.Length();
			lengthList.push_back(length);
		}

		bool isFar = false;
		//�O���[�v�S�����v���C���[���牓��������
		for (float& len : lengthList)
		{
			if (len > 8.0f) {
				isFar = true;
			}
			else {
				//�O���[�v�̈�l�ł��߂���΂��̂܂�
				isFar = false;
				break;
			}
		}

		if (isFar) {
			//�O���[�v�S�����v���C���[���牓��
			for (auto& enemy : groupList)
			{
				//�O���[�v�S���ɒʒm
				enemy->SetIsFind(false);
			}
		}
	}
}
