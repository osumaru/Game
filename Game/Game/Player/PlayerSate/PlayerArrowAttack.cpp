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
	GetPlayer().SetPlayerAnimation(GetPlayer().GetPlayerStateMachine().GetArrowState(), 0.5f);
	GetPlayer().SetAttack(true);
	//弓用の視点に変更
	GetGameCamera().SetCmareaState(GetGameCamera().enArrow);
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

		if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerArrowShoot)
		{
			GetPlayer().GetPlayerStateMachine().SetArrowAttackState(CPlayerState::enPlayerArrowAttack);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			//通常のカメラに戻す
			GetGameCamera().SetCmareaState(GetGameCamera().enNormal);
			GetPlayer().SetInitArrow(false);
		}

		else if (!m_isCharge)
		{
			GetPlayer().GetPlayerStateMachine().SetArrowAttackState(CPlayerState::enPlayerArrowShoot);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerArrowShoot);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);

		}
		
	}

}
