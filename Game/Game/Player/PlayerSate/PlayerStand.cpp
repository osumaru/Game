#include "stdafx.h"
#include "PlayerStand.h"
#include "IPlayerState.h"
#include "../Player.h"


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
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
	if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerWalk);

	}
	/*else if ((GetPlayer().GetMoveSpeed().Length()) >= 0.3f)
	{
		GetPlayer().SetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);

	}*/
}
