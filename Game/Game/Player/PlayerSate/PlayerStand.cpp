#include "stdafx.h"
#include "PlayerStand.h"
#include "IPlayerState.h"
#include "../Player.h"


CPlayerStand::CPlayerStand()
{
}


CPlayerStand::~CPlayerStand()
{
	
}
bool CPlayerStand::Start()
{
	//待機アニメーションの再生
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerStand, 0.2f);
	return true;
}

void CPlayerStand::Update()
{
	//移動の入力があるなら歩きアニメーションに遷移
	if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWalk);

	}
	/*else if ((GetPlayer().GetMoveSpeed().Length()) >= 0.3f)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);

	}*/
}
