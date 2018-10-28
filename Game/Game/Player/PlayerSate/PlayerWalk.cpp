#include "stdafx.h"
#include "PlayerWalk.h"
#include "../Player.h"



void CPlayerWalk::Init()
{
	//歩きアニメーションの再生
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerWalk, 0.2f);
}

void CPlayerWalk::Update()
{
	//移動の入力がなければ待機アニメーションに遷移
	if (Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}

	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerJump);
	}

	//一定以上の速さならあ知りアニメーションに遷移
	else if (fabs(GetPlayer().GetMoveSpeed().Length()) >= 1.3f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
	}

}
