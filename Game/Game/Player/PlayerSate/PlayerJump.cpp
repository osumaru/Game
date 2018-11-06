#include "stdafx.h"
#include "PlayerJump.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CPlayerJump::Init()
{
	CVector3 moveSpeed = m_pPlayer->GetMoveSpeed();
	moveSpeed.y += 20.0f;
	m_pPlayer->SetMoveSpeed(moveSpeed);
	if (m_pPlayer->GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerStateRunJump)
	{
		m_pPlayer->PlayAnimation(enPlayerAnimationRunJump, 0.0f);
	}
	else
	{
		m_pPlayer->PlayAnimation(enPlayerAnimationJump, 0.2f);
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
	CVector3 moveSpeed = m_pPlayer->GetMoveSpeed();
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
	if (abs(m_pPlayer->GetMoveSpeed().y - moveSpeed.y) > 10.0f)
	{
		throw;
	}
	m_pPlayer->SetMoveSpeed(moveSpeed);
	m_pPlayer->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	if (m_pPlayer->GetCharacterController().IsOnGround())
	{
		if (m_pPlayer->GetAnimation().GetCurrentAnimationNum() != enPlayerAnimationLanding)
		{
			m_pPlayer->SetMoveSpeed(CVector3::Zero);

			m_pPlayer->PlayAnimation(enPlayerAnimationLanding);
		}
		if (!m_pPlayer->GetAnimation().IsPlay())
		{
			//着地時移動していればランステートに、動いていなければスタンドステートに
			if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
			{
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
			}
		}
	}
	else if (m_pPlayer->GetWireAction().IsWireMove())
	{
		//ワイヤー移動できるなら遷移
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
}
