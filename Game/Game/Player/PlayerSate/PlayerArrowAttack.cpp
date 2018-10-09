#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"


CPlayerArrowAttack::CPlayerArrowAttack()
{
}


CPlayerArrowAttack::~CPlayerArrowAttack()
{
}

bool CPlayerArrowAttack::Start()
{
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerArrowAttack, 0.5f);
	GetPlayer().SetAttack(true);
	return true;
}

void CPlayerArrowAttack::Update()
{
	if (Pad().IsPressButton(enButtonX))
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
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
		}
	}

}
