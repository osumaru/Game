#include "stdafx.h"
#include "PlayerJump.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CPlayerJump::Init()
{
	CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	moveSpeed.y += 20.0f;
	m_pPlayerGetter->SetMoveSpeed(moveSpeed);
	if (m_pPlayer->GetStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerStateRunJump)
	{
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationRunJump, 0.0f);
	}
	else
	{
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationJump, 0.2f);
	}
}

void CPlayerJump::Update()
{
	const CCamera& gameCamera = GetGameCamera().GetCamera();
	CVector3 frontVec = gameCamera.GetTarget() - gameCamera.GetPosition();
	frontVec.y = 0.0f;
	frontVec.Normalize();
	CVector3 rightVec;
	rightVec.Cross(CVector3::AxisY, frontVec);
	rightVec.Normalize();
	CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	const float speed = 0.1f;
	moveSpeed += frontVec * Pad().GetLeftStickY() * speed;
	moveSpeed += rightVec * Pad().GetLeftStickX() * speed;
	CVector3 moveSpeedXZ = moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (LIMIT_MOVE_SPEED < moveSpeedXZ.Length())
	{
		moveSpeedXZ.Normalize();
		moveSpeedXZ.Scale(LIMIT_MOVE_SPEED);
		moveSpeed.x = moveSpeedXZ.x;
		moveSpeed.z = moveSpeedXZ.z;
	}
	if (abs(m_pPlayerGetter->GetMoveSpeed().y - moveSpeed.y) > 10.0f)
	{
		throw;
	}
	m_pPlayerGetter->SetMoveSpeed(moveSpeed);
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
	m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
	if (m_pPlayerGetter->GetCharacterController().IsOnGround())
	{
		if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() != enPlayerAnimationLanding)
		{
			m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);

			m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationLanding);
		}
		if (!m_pPlayerGetter->GetAnimation().IsPlay())
		{
			//着地時移動していればランステートに、動いていなければスタンドステートに
			if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
			}
		}
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove))
	{
		//ワイヤー移動できるなら遷移
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
}
