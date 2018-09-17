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
	if (GetPlayer().GetStatus().Health <= 0)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDied);
	}

	else if (GetPlayer().GetIsDamage())
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}

	else if (Pad().IsTriggerButton(enButtonX))
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAttack);
	}

	//移動の入力があるなら歩きアニメーションに遷移
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWalk);

	}
	
}
