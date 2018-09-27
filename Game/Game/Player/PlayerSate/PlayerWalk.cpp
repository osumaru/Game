#include "stdafx.h"
#include "PlayerWalk.h"
#include "../Player.h"


CPlayerWalk::CPlayerWalk()
{
}


CPlayerWalk::~CPlayerWalk()
{
}

bool CPlayerWalk::Start()
{
	//歩きアニメーションの再生
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerWalk, 0.2f);
	return true;
}

void CPlayerWalk::Update()
{
	//移動の入力がなければ待機アニメーションに遷移
	if (Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}

	//一定以上の速さならあ知りアニメーションに遷移
	else if (fabs(GetPlayer().GetMoveSpeed().Length()) >= 3.0f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
	}

}
