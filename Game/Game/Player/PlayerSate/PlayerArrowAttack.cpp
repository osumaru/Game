#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../Weapon/Bow.h"

void CPlayerArrowAttack::Init()
{
	//弓の生成
	dynamic_cast<CBow*>(m_pPlayer->GetWeaponManager().GetWeapon(enWeaponArrow))->ArrowCreate();
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowAttack, 0.5f);
	m_pPlayer->GetWeaponManager().SetIsAttack(true);
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	//弓用の視点に変更
	GetGameCamera().SetIsArrowZoom(true);
}

void CPlayerArrowAttack::Update()
{
	if (Pad().IsPressButton(enButtonRB))
	{
		m_isCharge = true;
	}
	else
	{
		m_isCharge = false;
	}

	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
		GetGameCamera().SetIsArrowZoom(false);
	}
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{

		if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowShoot))
		{

			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowShoot);
		}
		
	}

}
