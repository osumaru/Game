#include "stdafx.h"
#include "PlayerStand.h"
#include "PlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include "../../Scene/SceneManager.h"
#include "../Weapon/WeaponManager.h"
#include "../../Command/Command.h"

void CPlayerStand::Init()
{
	IPlayerState::Init();
	m_isStateTransition = true;
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
		m_pPlayer->SetCommand(new DiedCommand(m_pPlayer));

	}
	//ダメージを受けた場合の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->SetCommand(new DamageCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStun))
	{
		m_pPlayer->SetCommand(new StunCommand(m_pPlayer));
	}
	//攻撃をした時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_pPlayer->SetCommand(new ArrowAttackCommand(m_pPlayer));
	}
	//攻撃をした時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAttack))
	{
		m_pPlayer->SetCommand(new AttackCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateJump))
	{
		m_pPlayer->SetCommand(new JumpCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance))
	{
		m_pPlayer->SetCommand(new AvoidanceCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove)) 
	{
		//ワイヤー移動できるなら遷移
		m_pPlayer->SetCommand(new WireMoveCommand(m_pPlayer));
	}
	//移動の入力があるなら歩きアニメーションに遷移
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
	{
		//GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateWalk);
		m_pPlayer->SetCommand(new RunCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateSky))
	{
		m_pPlayer->SetCommand(new SkyCommand(m_pPlayer));
	}
}
void CPlayerStand::ChangeWepon()
{
	
}
