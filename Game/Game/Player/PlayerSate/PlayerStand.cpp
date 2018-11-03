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
	m_pPlayer->PlayAnimation(enPlayerAnimationStand);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
}

void CPlayerStand::Update()
{
	
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
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateJump);
	}

	else if (Pad().IsTriggerButton(enButtonB))
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	else if (m_pPlayer->GetWireAction().IsWireMove()) 
	{
		//���C���[�ړ��ł���Ȃ�J��
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
