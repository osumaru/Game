#include "stdafx.h"
#include "PlayerStand.h"
#include "IPlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include"../../Scene/SceneManager.h"


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
	ChangeWepon();
	//死亡した場合の処理
	if (GetPlayer().GetStatus().Health <= 0)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDied);
	}
	//ダメージを受けた場合の処理
	else if (GetPlayer().GetIsDamage())
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}
	//攻撃をした時の処理
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
void CPlayerStand::ChangeWepon()
{
	GetPlayer().SetChangeWeapon(GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon());

}
