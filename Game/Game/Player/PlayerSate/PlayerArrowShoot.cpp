#include "stdafx.h"
#include "PlayerArrowShoot.h"
#include "../Player.h"


CPlayerArrowShoot::CPlayerArrowShoot()
{
}


CPlayerArrowShoot::~CPlayerArrowShoot()
{
}

void CPlayerArrowShoot::Init()
{
	//�|��ł��[�V����
	m_pPlayer->PlayAnimation(enPlayerAnimationArrowShoot, 0.5f);
	m_pPlayer->SetIsAttack(true);
	m_isShoot = false;
}

void CPlayerArrowShoot::Update()
{
	if (Pad().GetRightTrigger())
	{
		m_isShoot = true;
	}


	if (!GetPlayer().GetAnimation().IsPlay())
	{
		//�A�ˎ��̏���
		if (m_isShoot)
		{
			GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
		}
		else
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
			m_pPlayer->SetIsAttack(false);

		}
	}


}
