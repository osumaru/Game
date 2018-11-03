#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
#include "../WireAction.h"

void CPlayerWireMove::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationWireMove, 0.1f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();
}

void CPlayerWireMove::Update()
{
	CVector3 playerPos = m_pPlayer->GetPosition();
	bool isMoveEnd = false;
	CVector3 toMovePos = m_movePosition - playerPos;

	float length = toMovePos.Length();
	if (length > 2.0f) {
		//�ڕW�Ƃ̋���������Ă���Έړ���ɐi��
		toMovePos.Normalize();
		toMovePos *= m_speed;
		GetPlayer().SetMoveSpeed(toMovePos);
		m_pPlayer->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
	}
	else {
		m_pPlayer->GetWireAction().SetIsWireMove(false);
		isMoveEnd = true;
	}

	if (isMoveEnd) {
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		switch (m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			//�ړ����I�������G�̃t���O��߂��Ă��
			for (auto& enemy : enemyList)
			{
				enemy->SetIsWireHit(false);
			}
			break;
		case CWireAction::enStateMap:
			break;
		}

		//�ړ����I�����
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}
