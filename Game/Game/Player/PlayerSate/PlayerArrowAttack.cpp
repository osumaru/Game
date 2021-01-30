#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../Weapon/Bow.h"
#include "../../Command/Command.h"

void CPlayerArrowAttack::Init()
{
	IPlayerState::Init();
	m_isStateTransition = true;
	//ã|ÇÃê∂ê¨
	dynamic_cast<CBow*>(m_pPlayer->GetWeaponManager().GetWeapon(enWeaponArrow))->ArrowCreate();
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowAttack, 0.5f);
	m_pPlayer->GetWeaponManager().SetIsAttack(true);
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	//ã|ópÇÃéãì_Ç…ïœçX
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
		m_pPlayer->SetCommand(new DamageCommand(m_pPlayer));
		GetGameCamera().SetIsArrowZoom(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStun))
	{
		m_pPlayer->SetCommand(new StunCommand(m_pPlayer));
		GetGameCamera().SetIsArrowZoom(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
	}
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{

		if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowShoot))
		{

			m_pPlayer->SetCommand(new ArrowShootCommand(m_pPlayer));
		}
		
	}

}
