#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

bool CPlayerWireMove::Start()
{
	float minLength = FLT_MAX;
	std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
	//���C���[���΂�������߂�
	for (auto& enemy : enemyList)
	{
		CVector3 enemyPos = enemy->GetPosition();
		CVector3 toEnemyPos = enemyPos - GetPlayer().GetPosition();
		float length = toEnemyPos.Length();
		if (minLength > length) {
			minLength = length;
			//��ԋ߂��G�̈ʒu���ړ���Ƃ���
			m_movePosition = enemyPos;
		}
	}

	//��ԋ߂��G�Ƀ��C���[�����������t���O��ݒ肷��
	for (auto& enemy : enemyList) 
	{
		CVector3 enemyPos = enemy->GetPosition();
		CVector3 toMovePos = m_movePosition - enemyPos;
		float length = toMovePos.Length();
		if (length < 0.1f) {
			enemy->SetIsWireHit(true);
		}
	}

	return true;
}

void CPlayerWireMove::Update()
{
	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toMovePos = m_movePosition - playerPos;

	float length = toMovePos.Length();
	if (length > 1.5f) {
		//�G�Ƃ̋���������Ă���Έړ���ɐi��
		toMovePos.Normalize();
		toMovePos *= m_speed;
		GetPlayer().SetMoveSpeed(toMovePos);
	}
	else {
		isMoveEnd = true;
	}

	if (isMoveEnd) {
		//�ړ����I�������G�̃t���O��߂��Ă��
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		for (auto& enemy : enemyList)
		{
			CVector3 enemyPos = enemy->GetPosition();
			CVector3 toMovePos = m_movePosition - enemyPos;
			float length = toMovePos.Length();
			if (length < 0.1f) {
				enemy->SetIsWireHit(false);
			}
		}
	}

	if (isMoveEnd) {
		//�ړ����I�����
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}
}
