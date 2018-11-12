#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"

CPlayerAttack::CPlayerAttack()
{
	m_attackAnimation[0] = enPlayerAnimationAttack;
	m_attackAnimation[1] = enPlayerAnimationAttack2;
	m_attackAnimation[2] = enPlayerAnimationAttack3;
}

void CPlayerAttack::Init()
{

	m_pPlayer->SetMoveSpeed(CVector3::Zero);
	m_attackCount = 0;
	m_isContinuationAttack = false;
	m_animetionFrame = 0.0f;
	m_pPlayer->PlayAnimation(m_attackAnimation[m_attackCount], 0.2f);
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.3f)
	{
		m_pPlayer->SetIsAttack(true);
	}
	//�U�����ɍU���̓��͂����ꂽ�ꍇ�͘A���Ɉڍs����
	if (Pad().IsTriggerButton(enButtonRightTrigger) && !m_isContinuationAttack && m_attackCount < MAX_ATTACK_NUM - 1)
	{
		m_isContinuationAttack = true;
		m_attackCount++;
	}

	//�U���A�j���[�V�������I��������̏���
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		m_pPlayer->SetIsAttack(false);
		//�U�����[�V�������̓_���[�W���[�V�����������Ȃ�
		if (m_isContinuationAttack)
		{
			m_isContinuationAttack = false;
			m_animetionFrame = 0.0f;
			m_pPlayer->PlayAnimation(m_attackAnimation[m_attackCount], 0.2f);
		}
		else
		{
			if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
			{
				//����A�j���[�V����
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);

			}
		}
	}
}
