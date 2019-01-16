#include "stdafx.h"
#include "PlayerSky.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include "../../Scene/SceneManager.h"
#include "../Weapon/WeaponManager.h"


CPlayerSky::CPlayerSky()
{
}

void CPlayerSky::Init()
{
	//アニメーションの再生
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
	
	//地面についていたら着地モーションを流す
	if (m_pPlayerGetter->GetCharacterController().IsOnGround())
	{
		if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() != enPlayerAnimationLanding)
		{
			m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);

			m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationLanding);
		}
		if (!m_pPlayerGetter->GetAnimation().IsPlay())
		{
			//着地時移動していればランステートに、動いていなければスタンドステートに
			if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
			}
		}
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove))
	{
		//ワイヤー移動できるなら遷移
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}


}