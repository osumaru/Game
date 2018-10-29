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
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerStand,0.5f);
}

void CPlayerStand::Update()
{
	
	//���S�����ꍇ�̏���
	if (GetPlayer().GetStatus().Health <= 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDied);
	}
	//�_���[�W���󂯂��ꍇ�̏���
	else if (GetPlayer().GetIsDamage())
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}
	//�U�����������̏���
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
		//���C���[�ړ��ł���Ȃ�J��
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWireMove);
	}
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWalk);

	}
	
}
void CPlayerStand::ChangeWepon()
{
	
}
