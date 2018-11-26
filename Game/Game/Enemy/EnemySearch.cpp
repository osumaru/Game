#include "stdafx.h"
#include "EnemySearch.h"
#include "IEnemy.h"
#include "../Player/Player.h"
#include "EnemyGroup.h"

void CEnemySearch::Update()
{
	//�v���C���[�Ƃ̋������v�Z
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 distance = playerPos - m_enemy->GetPosition();
	float length = distance.Length();
	//������Ƀv���C���[�����邩����
	bool isFindPlayer = m_enemy->CalucFanShape(45.0f, playerPos);

	if (isFindPlayer && length < 15.0f || m_enemy->IsDamage() || m_enemy->IsWireHit()) {
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
		if (&m_enemy->GetEnemyGroup()->GetGroupList() == NULL) { return; }
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
