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
	m_pPlayer->PlayAnimation(enPlayerAnimationStand,0.5f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
}

void CPlayerStand::Update()
{
	if (m_pPlayer->GetAnimation().GetCurrentAnimationNum() != enPlayerAnimationStand)
	{
		if (!m_pPlayer->GetAnimation().IsPlay())
		{
			m_pPlayer->PlayAnimation(enPlayerAnimationStand);
		}
		return;
	}
	//死亡した場合の処理
	if (m_pPlayer->GetStatus().Health <= 0)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateDied);
	}
	//ダメージを受けた場合の処理
	else if (m_pPlayer->GetIsDamage())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	//攻撃をした時の処理
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if (m_pPlayer->GetWeapon().GetCurrentState() == CWeapon::enArrow)
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
		}
		else
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateAttack);
		}
		
	}
	
	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateJump);
	}

	else if (Pad().IsTriggerButton(enButtonB))
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	else if (GetPlayer().GetWireAction().IsWireMove()) 
	{
		//ワイヤー移動できるなら遷移
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	//移動の入力があるなら歩きアニメーションに遷移
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
