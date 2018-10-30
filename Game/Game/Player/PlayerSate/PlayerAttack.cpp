#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"

CPlayerAttack::CPlayerAttack()
{
	m_attackAnimation[0] = enPlayerAnimationAttack;
	m_attackAnimation[1] = enPlayerAnimationAttack2;
}

void CPlayerAttack::Init()
{

	m_pPlayer->SetMoveSpeed(CVector3::Zero);
	m_attackCount = 0;
	m_isContinuationAttack = false;
	m_animetionFrame = 0.0f;
	m_pPlayer->SetPlayerAnimation(m_attackAnimation[m_attackCount], 0.2f);
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.3f)
	{
		m_pPlayer->SetAttack(true);
	}
	//攻撃中に攻撃の入力がされた場合は連撃に移行する
	if (Pad().IsTriggerButton(enButtonRightTrigger) && !m_isContinuationAttack && m_attackCount < MAX_ATTACK_NUM - 1)
	{
		m_isContinuationAttack = true;
		m_attackCount++;
	}

	//攻撃アニメーションが終わった時の処理
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		m_pPlayer->SetAttack(false);
		//攻撃モーション中はダメージモーションをさせない
		if (m_isContinuationAttack)
		{
			m_isContinuationAttack = false;
			m_animetionFrame = 0.0f;
			m_pPlayer->SetAnimationPlay(m_attackAnimation[m_attackCount], 0.2f);
		}
		else
		{
			if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
			{
				//走りアニメーション
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);

			}
		}
	}
}
