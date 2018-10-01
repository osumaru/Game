#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"


CPlayerAttack::CPlayerAttack()
{
}


CPlayerAttack::~CPlayerAttack()
{
}

bool CPlayerAttack::Start()
{

	GetPlayer().SetPlayerAnimation(GetPlayer().GetPlayerStateMachine().GetAttackSate(), 0.2f);
	return true;
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.6f)
	{
		GetPlayer().SetAttack(true);

	}

	//攻撃アニメーションが終わった時の処理
	if (m_animetionFrame >= 1.3f/*!GetPlayer().GetAnimetion().IsPlay()*/)
	{
		//攻撃モーション中はダメージモーションをさせない
		if (GetPlayer().GetIsDamage())
		{

			
		}
		if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
		{
			//走りアニメーション
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			m_animetionFrame = 0.0f;
		}

		else
		{
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			m_animetionFrame = 0.0f;

		}
	}
}
