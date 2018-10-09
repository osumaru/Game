#include "stdafx.h"
#include "PlayerStand.h"
#include "IPlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include"../../Scene/SceneManager.h"


CPlayerStand::CPlayerStand()
{
}


CPlayerStand::~CPlayerStand()
{
	
}
bool CPlayerStand::Start()
{
	//�ҋ@�A�j���[�V�����̍Đ�
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerStand,0.5f);
	return true;
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
	else if (Pad().IsTriggerButton(enButtonX))
	{
		if (GetPlayer().GetPlayerStateMachine().GetAttackSate() == CPlayerState::enPlayerArrowAttack)
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

	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAvoidance);
	}
	else if (Pad().IsTriggerButton(enButtonY)) 
	{
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
