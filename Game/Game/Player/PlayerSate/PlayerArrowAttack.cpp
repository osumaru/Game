#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"


void CPlayerArrowAttack::Init()
{
	//弓の生成
	GetPlayer().InitArrow();
	GetPlayer().SetPlayerAnimation(CPlayerState::enPlayerArrowAttack, 0.5f);
	GetPlayer().SetAttack(true);
	//弓用の視点に変更
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
