#include "stdafx.h"
#include "PlayerArrowShoot.h"
#include "../Player.h"


CPlayerArrowShoot::CPlayerArrowShoot()
{
}


CPlayerArrowShoot::~CPlayerArrowShoot()
{
}

bool CPlayerArrowShoot::Start()
{
	//�|��ł��[�V����
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerArrowShoot, 0.5f);
	GetPlayer().SetAttack(true);
	m_isShoot = false;
	return true;
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
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{

			GetPlayer().GetPlayerStateMachine().SetArrowAttackState(CPlayerState::enPlayerArrowAttack);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);

		}
	}


}
