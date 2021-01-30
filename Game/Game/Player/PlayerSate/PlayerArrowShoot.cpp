#include "stdafx.h"
#include "PlayerArrowShoot.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"
#include "../../Command/Command.h"

CPlayerArrowShoot::CPlayerArrowShoot()
{
}


CPlayerArrowShoot::~CPlayerArrowShoot()
{
}

void CPlayerArrowShoot::Init()
{
	IPlayerState::Init();
	m_isStateTransition = true;
	const float ArrowVolume = 0.3f;
	CSoundSource* ArrowSound = New<CSoundSource>(0);
	ArrowSound->Init("Assets/sound/Battle/ArrowSound.wav");
	ArrowSound->Play(false);
	ArrowSound->SetVolume(ArrowVolume);
	//�|��ł��[�V����
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationArrowShoot, 0.5f);
	m_isShoot = false;
}

void CPlayerArrowShoot::Update()
{
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

	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_isShoot = true;
	}


	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//�A�ˎ��̏���
		if (m_isShoot)
		{
			m_pPlayer->SetCommand(new ArrowAttackCommand(m_pPlayer));
		}
		else
		{

			m_pPlayer->SetCommand(new StandCommand(m_pPlayer));
			m_pPlayer->GetWeaponManager().SetIsAttack(false);
			GetGameCamera().SetIsArrowZoom(false);
		}
	}


}
