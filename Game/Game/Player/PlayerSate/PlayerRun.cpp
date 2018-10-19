#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"



CPlayerRun::CPlayerRun()
{
}


CPlayerRun::~CPlayerRun()
{
}
bool CPlayerRun::Start()
{
	
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerRun, 0.2f);
	
	return true;
}

void CPlayerRun::Update()
{
	//���蒆�Ƀ_���[�W���󂯂��ꍇ
	if (GetPlayer().GetIsDamage())
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerDamage);
	}
	//�����Ă���Ƃ��ɍU���������̏���
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if(GetPlayer().GetPlayerStateMachine().GetAttackSate() == CPlayerState::enPlayerArrowAttack)
		{
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{

			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAttack);
		}
	}
	//���蒆�ɉ���������̏���
	else if (Pad().IsTriggerButton(enButtonB))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerAvoidance);
	}
	//�����Ă��鎞�ɃW�����v�������ꂽ�Ƃ�����
	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRunJump);
	}

	else if (fabs(GetPlayer().GetMoveSpeed().Length()) == 0.0f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}
	else if (GetPlayer().IsWireMove()) 
	{
		//���C���[�ړ��ł���Ȃ�J��
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWireMove);
	}
}