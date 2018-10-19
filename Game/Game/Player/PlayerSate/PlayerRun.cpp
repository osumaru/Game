#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"



CPlayerRun::CPlayerRun()
{
}


CPlayerRun::~CPlayerRun()
{
}
bool CPlayerRun::Start()
{
	
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerRun, 0.2f);
	
	return true;
}

void CPlayerRun::Update()
{
	//走り中にダメージを受けた場合
	if (GetPlayer().GetIsDamage())
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}
	//走っているときに攻撃した時の処理
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if(GetPlayer().GetPlayerStateMachine().GetAttackSate() == CPlayerState::enPlayerArrowAttack)
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