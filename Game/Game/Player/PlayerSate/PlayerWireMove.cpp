#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

void CPlayerWireMove::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireThrow, 0.25f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();
	m_accel = 0.0f;
	m_moveSpeed = 0.0f;
	m_wireSpeed = 1.0f;
	m_isWireThrow = true;
	//ワイヤーの始点を決める
	m_playerHandMatrix = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftHand");
	m_playerHandPos.x = m_playerHandMatrix->m[3][0];
	m_playerHandPos.y = m_playerHandMatrix->m[3][1];
	m_playerHandPos.z = m_playerHandMatrix->m[3][2];
	m_pPlayerGetter->GetWireDraw().SetStartPosition(m_playerHandPos);
	//ワイヤーの終点を決める
	CVector3 wireDir = m_movePosition - m_playerHandPos;
	wireDir.Normalize();
	wireDir *= m_wireSpeed;
	m_wireSpeed += m_wireSpeed;
	CVector3 wireEndPos = m_playerHandPos + wireDir;
	m_pPlayerGetter->GetWireDraw().SetEndPosition(wireEndPos);
}

void CPlayerWireMove::Update()
{
	//ワイヤーの始点を決める
	m_playerHandPos.x = m_playerHandMatrix->m[3][0];
	m_playerHandPos.y = m_playerHandMatrix->m[3][1];
	m_playerHandPos.z = m_playerHandMatrix->m[3][2];
	m_pPlayerGetter->GetWireDraw().SetStartPosition(m_playerHandPos);
	//ワイヤーの終点を決める
	CVector3 wireDir = m_movePosition - m_playerHandPos;
	wireDir.Normalize();
	wireDir *= m_wireSpeed;
	m_wireSpeed += m_wireSpeed;
	CVector3 wireEndPos = m_playerHandPos + wireDir;
	m_pPlayerGetter->GetWireDraw().SetEndPosition(wireEndPos);
	//ワイヤー描画を更新
	m_pPlayerGetter->GetWireDraw().Update();
	//ワイヤーを投げるアニメーションが終了したか判定
	if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationWireThrow
		&& !m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//ワイヤー移動するアニメーションに切り替え
		m_isWireThrow = false;
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireMove, 0.25f);
	}

	if (m_isWireThrow)
	{
		//ワイヤーを投げるアニメーションをしている
		return;
	}

	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toMovePos = m_movePosition - playerPos;

	float length = toMovePos.Length();
	toMovePos.Normalize();
	m_accel += 0.3f;
	m_moveSpeed += m_accel;
	if (m_speed < m_moveSpeed)
	{
		m_moveSpeed = m_speed;
	}
	toMovePos *= m_moveSpeed;
	float range = 2.0f;

	switch (m_pPlayer->GetWireAction().GetState())
	{
	case CWireAction::enStateEnemy:
		range = 2.0f;
		break;
	case CWireAction::enStateMap:
		range = 3.0f;
		break;
	}
	if (length > range) {
		//目標との距離が離れていれば移動先に進む
		m_pPlayerGetter->SetMoveSpeed(toMovePos);
		m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
	}
	else {
		isMoveEnd = true;
	}

	if (isMoveEnd) {
		//移動が終わった
		GetPlayer().GetWireAction().SetIsWireMove(false);
		std::list<IEnemy*> enemyList = GetSceneGame().GetMap()->GetEnemyList();
		switch(m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireAttack);
			//移動し終わったら敵のフラグを戻してやる
			for (auto& enemy : enemyList)
			{
				if (enemy->IsWireHit()) {
					//ワイヤーが当たっていたらダメージ
					enemy->SetIsDamage(true);
				}
				enemy->SetIsWireHit(false);
			}
			break;
		case CWireAction::enStateMap:
			if (Pad().IsPressButton(enButtonRightTrigger))
			{
				toMovePos.y = 10.0f;
				m_pPlayerGetter->SetMoveSpeed(toMovePos);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
			}
			else
			{
				m_pPlayerGetter->SetPosition(m_movePosition);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
				m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationLanding);
			}
			break;
		}
	}
}
