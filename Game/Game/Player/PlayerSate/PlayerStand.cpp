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
	m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerStand,0.5f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
}

void CPlayerStand::Update()
{
	
	//���S�����ꍇ�̏���
	if (m_pPlayer->GetStatus().Health <= 0)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerDied);
	}
	//�_���[�W���󂯂��ꍇ�̏���
	else if (m_pPlayer->GetIsDamage())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerDamage);
	}
	//�U�����������̏���
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
		//���C���[�ړ��ł���Ȃ�J��
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerWireMove);
	}
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
