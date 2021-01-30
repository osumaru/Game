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
	//�ҋ@�A�j���[�V�����̍Đ�
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
	//���S�����ꍇ�̏���
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDied))
	{
		m_pPlayer->SetCommand(new DiedCommand(m_pPlayer));

	}
	//�_���[�W���󂯂��ꍇ�̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->SetCommand(new DamageCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStun))
	{
		m_pPlayer->SetCommand(new StunCommand(m_pPlayer));
	}
	//�U�����������̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_pPlayer->SetCommand(new ArrowAttackCommand(m_pPlayer));
	}
	//�U�����������̏���
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
		//���C���[�ړ��ł���Ȃ�J��
		m_pPlayer->SetCommand(new WireMoveCommand(m_pPlayer));
	}
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
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
