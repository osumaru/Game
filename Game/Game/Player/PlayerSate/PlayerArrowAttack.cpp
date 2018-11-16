#include "stdafx.h"
#include "PlayerArrowAttack.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../Weapon/Bow.h"

void CPlayerArrowAttack::Init()
{
	//ã|ÇÃê∂ê¨
	dynamic_cast<CBow*>(m_pPlayer->GetWeaponManager().GetWeapon(CWeaponManager::enArrow))->ArrowCreate();
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowAttack, 0.5f);
	m_pPlayer->GetWeaponManager().SetIsAttack(true);
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	//ã|ópÇÃéãì_Ç…ïœçX
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

	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{

		if (!m_isCharge)
		{

			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowShoot);
		}
		
	}

}
