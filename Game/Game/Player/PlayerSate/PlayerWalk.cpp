#include "stdafx.h"
#include "PlayerWalk.h"
#include "../Player.h"


CPlayerWalk::CPlayerWalk()
{
}


CPlayerWalk::~CPlayerWalk()
{
}

bool CPlayerWalk::Start()
{
	//�����A�j���[�V�����̍Đ�
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerWalk, 0.2f);
	return true;
}

void CPlayerWalk::Update()
{
	//�ړ��̓��͂��Ȃ���Αҋ@�A�j���[�V�����ɑJ��
	if (Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
	}

	//���ȏ�̑����Ȃ炠�m��A�j���[�V�����ɑJ��
	else if (fabs(GetPlayer().GetMoveSpeed().Length()) >= 3.0f)
	{
		GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
	}

}
