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
	m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerStand,0.5f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
}

void CPlayerStand::Update()
{
	
	//死亡した場合の処理
	if (m_pPlayer->GetStatus().Health <= 0)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerDied);
	}
	//ダメージを受けた場合の処理
	else if (m_pPlayer->GetIsDamage())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerDamage);
	}
	//攻撃をした時の処理
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if (m_pPlayer->GetWeapon().GetCurrentState() == CWeapon::enWeaponArrow)
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerAttack);
		}
		
	}
	
	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerJump);
	}

	else if (Pad().IsTriggerButton(enButtonB))
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerAvoidance);
	}
	else if (GetPlayer().IsWireMove()) 
	{
		//ワイヤー移動できるなら遷移
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerWireMove);
	}
	//移動の入力があるなら歩きアニメーションに遷移
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
