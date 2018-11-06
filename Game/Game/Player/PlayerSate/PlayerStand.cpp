#include "stdafx.h"
#include "PlayerStand.h"
#include "PlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include"../../Scene/SceneManager.h"
#include "../Weapon.h"

void CPlayerStand::Init()
{
	//�ҋ@�A�j���[�V�����̍Đ�
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
	//���S�����ꍇ�̏���
	if (m_pPlayer->GetStatus().Health <= 0)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateDied);
	}
	//�_���[�W���󂯂��ꍇ�̏���
	else if (m_pPlayer->GetIsDamage())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	//�U�����������̏���
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
		//���C���[�ړ��ł���Ȃ�J��
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
