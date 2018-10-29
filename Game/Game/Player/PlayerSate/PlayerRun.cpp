#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CPlayerRun::Init()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerRun, 0.2f);
}

void CPlayerRun::Update()
{
	const CCamera& gameCamera = GetGameCamera().GetCamera();
	CVector3 frontVec = gameCamera.GetTarget() - gameCamera.GetPosition();
	frontVec.y = 0.0f;
	frontVec.Normalize();
	CVector3 rightVec;
	rightVec.Cross(CVector3::AxisY, frontVec);
	rightVec.Normalize();
	CVector3 moveSpeed = m_pPlayer->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	const float speed = 4.0f;
	moveSpeed += frontVec * Pad().GetLeftStickY() * speed;
	moveSpeed += rightVec * Pad().GetLeftStickX() * speed;
	m_pPlayer->SetMoveSpeed(moveSpeed);

	//走り中にダメージを受けた場合
	if (GetPlayer().GetIsDamage())
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}
	//走っているときに攻撃した時の処理
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if(m_pPlayer->GetWeapon().GetCurrentState() == CWeapon::enWeaponArrow)
		{
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{

			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAttack);
		}
	}
	//走り中に回避した時の処理
	else if (Pad().IsTriggerButton(enButtonB))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAvoidance);
	}
	//走っている時にジャンプが押されたとき処理
	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRunJump);
	}

	else if (fabs(GetPlayer().GetMoveSpeed().Length()) == 0.0f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}
	else if (GetPlayer().IsWireMove()) 
	{
		//ワイヤー移動できるなら遷移
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWireMove);
	}
}