#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"


CPlayerArrowAttack::CPlayerArrowAttack()
{
}


CPlayerArrowAttack::~CPlayerArrowAttack()
{
}

bool CPlayerArrowAttack::Start()
{
	//ã|ÇÃê∂ê¨
	GetPlayer().InitArrow();
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerArrowAttack, 0.5f);
	GetPlayer().SetAttack(true);
	//ã|ópÇÃéãì_Ç…ïœçX
	return true;
}

void CPlayerArrowAttack::Update()
{
	if (Pad().IsPressButton(enButtonRightTrigger))
	{
		m_isCharge = true;
	}
	else
	{
		m_isCharge = false;
	}

	if (!GetPlayer().GetAnimation().IsPlay())
	{

		if (!m_isCharge)
		{

			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerArrowShoot);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
		}
		
	}

}
