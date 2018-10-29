#include "stdafx.h"
#include "PlayerWalk.h"
#include "../Player.h"



void CPlayerWalk::Init()
{
	//�����A�j���[�V�����̍Đ�
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerWalk, 0.2f);
}

void CPlayerWalk::Update()
{
	//�ړ��̓��͂��Ȃ���Αҋ@�A�j���[�V�����ɑJ��
	if (Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}

	else if (Pad().IsTriggerButton(enButtonA))
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerJump);
	}

	//���ȏ�̑����Ȃ炠�m��A�j���[�V�����ɑJ��
	else if (fabs(GetPlayer().GetMoveSpeed().Length()) >= 1.3f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
	}

}
