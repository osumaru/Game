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
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerStand, 0.2f);
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
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAttack);
	}
	
	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerJump);
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
