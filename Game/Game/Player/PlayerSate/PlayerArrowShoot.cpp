#include "stdafx.h"
#include "PlayerArrowShoot.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

CPlayerArrowShoot::CPlayerArrowShoot()
{
}


CPlayerArrowShoot::~CPlayerArrowShoot()
{
}

void CPlayerArrowShoot::Init()
{
	const float ArrowVolume = 0.3f;
	CSoundSource* ArrowSound = New<CSoundSource>(0);
	ArrowSound->Init("Assets/sound/Battle/ArrowSound.wav");
	ArrowSound->Play(false);
	ArrowSound->SetVolume(ArrowVolume);
	//‹|‚ð‘Å‚Âƒ‚[ƒVƒ‡ƒ“
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowShoot, 0.5f);
	m_isShoot = false;
}

void CPlayerArrowShoot::Update()
{
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
		GetGameCamera().SetIsArrowZoom(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStun))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStun);
		GetGameCamera().SetIsArrowZoom(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
	}

	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_isShoot = true;
	}


	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//˜AŽËŽž‚Ìˆ—
		if (m_isShoot)
		{
			GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
		}
		else
		{
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
			m_pPlayer->GetWeaponManager().SetIsAttack(false);
			GetGameCamera().SetIsArrowZoom(false);
		}
	}


}
