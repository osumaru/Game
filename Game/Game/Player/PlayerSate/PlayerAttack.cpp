#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"



void CPlayerAttack::Init()
{
	GetPlayer().SetPlayerAnimation(GetPlayer().GetPlayerStateMachine().GetAttackSate(), 0.2f);
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.3f)
	{
		GetPlayer().SetAttack(true);

	}
	//攻撃中に攻撃の入力がされた場合は連撃に移行する
	if (Pad().IsTriggerButton(enButtonRightTrigger) && !m_rock)
	{
		m_conAtaack = true;
		m_rock = true;
		GetPlayer().GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack2);
	}

	//攻撃アニメーションが終わった時の処理
	if (!GetPlayer().GetAnimation().IsPlay())
	{
		//攻撃モーション中はダメージモーションをさせない
		if (m_conAtaack)
		{
			Init();
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			m_conAtaack = false;
			m_animetionFrame = 0.0f;
		}
		else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
		{
			//走りアニメーション
			GetPlayer().GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerRun);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			m_rock = false;
			m_animetionFrame = 0.0f;
		}

		else
		{
			GetPlayer().GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
			GetPlayer().GetPlayerStateMachine().ChangeState(CPlayerState::enPlayerStand);
			GetPlayer().GetWeaponBody().PhysicsWorldRemoveRigidBody();
			GetPlayer().SetAttack(false);
			m_rock = false;
			m_animetionFrame = 0.0f;

		}
	}
}
