#include "stdafx.h"
#include "PlayerStand.h"
#include "PlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include "../../Scene/SceneManager.h"
#include "../Weapon/WeaponManager.h"

void CPlayerStand::Init()
{
	//待機アニメーションの再生
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationStand, 0.5f);
	if (m_pPlayer->GetWeaponManager().GetDrawingWeapon())
	{
		const IWeapon* weapon = m_pPlayer->GetWeaponManager().GetWeapon();
		m_pPlayerGetter->GetAnimation().AddBlendAnimation(weapon->GetWeaponHorldBoneID(IWeapon::enAnimationBlendStand), weapon->GetWeaponHoldAnimationNum(IWeapon::enAnimationBlendStand));
	}
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
}

void CPlayerStand::Update()
{
	//if (m_pPlayerGetter->GetAnimation().IsInterpolation())
	//{
	//	return;
	//}
	if (!m_pPlayer->GetWeaponManager().GetDrawingWeapon())
	{
		m_pPlayerGetter->GetAnimation().BlendAnimationClear();
	}
	//死亡した場合の処理
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDied))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDied);
	}
	//ダメージを受けた場合の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStun))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStun);
	}
	//攻撃をした時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
	}
	//攻撃をした時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAttack);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateJump))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove)) 
	{
		//ワイヤー移動できるなら遷移
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	//移動の入力があるなら歩きアニメーションに遷移
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
	{
		//GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateWalk);
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateSky))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
	}
}
void CPlayerStand::ChangeWepon()
{
	
}
