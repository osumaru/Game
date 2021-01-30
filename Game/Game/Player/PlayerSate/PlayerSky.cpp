#include "stdafx.h"
#include "PlayerSky.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include "../../Scene/SceneManager.h"
#include "../Weapon/WeaponManager.h"
#include "../../Command/Command.h"


CPlayerSky::CPlayerSky()
{
}

void CPlayerSky::Init()
{
	IPlayerState::Init();
	m_isStateTransition = true;
	//�A�j���[�V�����̍Đ�
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationJump, 0.2f);
}

void CPlayerSky::Update()
{
	//if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationLanding)
	//{
	//	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	//}
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
	
	//�n�ʂɂ��Ă����璅�n���[�V�����𗬂�
	if (m_pPlayerGetter->GetCharacterController().IsOnGround())
	{
		if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() != enPlayerAnimationLanding)
		{
			const float landingVolume = 0.3f;
			CSoundSource* landingSound = New<CSoundSource>(0);
			landingSound->Init("Assets/sound/Battle/Groundlanding.wav");
			landingSound->Play(false);
			landingSound->SetVolume(landingVolume);
			m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);

			m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationLanding);
		}
		if (!m_pPlayerGetter->GetAnimation().IsPlay())
		{
			//���n���ړ����Ă���΃����X�e�[�g�ɁA�����Ă��Ȃ���΃X�^���h�X�e�[�g��
			if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
			{
				m_pPlayer->SetCommand(new RunCommand(m_pPlayer));
			}
			else
			{
				m_pPlayer->SetCommand(new StandCommand(m_pPlayer));
			}
		}
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->SetCommand(new DamageCommand(m_pPlayer));
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove))
	{
		//���C���[�ړ��ł���Ȃ�J��
		m_pPlayer->SetCommand(new WireMoveCommand(m_pPlayer));
	}


}