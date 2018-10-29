#include "stdafx.h"
#include "PlayerStand.h"
#include "PlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include"../../Scene/SceneManager.h"
#include "../Weapon.h"

void CPlayerStand::Init()
{
	//待機アニメーションの再生
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerStand,0.5f);
}

void CPlayerStand::Update()
{
	
	//死亡した場合の処理
	if (GetPlayer().GetStatus().Health <= 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDied);
	}
	//ダメージを受けた場合の処理
	else if (GetPlayer().GetIsDamage())
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}
	//攻撃をした時の処理
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if (m_pPlayer->GetWeapon().GetCurrentState() == CWeapon::enWeaponArrow)
		{
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAttack);
		}
		
	}
	
	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerJump);
	}

	else if (Pad().IsTriggerButton(enButtonB))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAvoidance);
	}
	else if (GetPlayer().IsWireMove()) 
	{
		//ワイヤー移動できるなら遷移
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWireMove);
	}
	//移動の入力があるなら歩きアニメーションに遷移
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
