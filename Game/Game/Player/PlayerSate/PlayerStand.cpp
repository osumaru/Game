#include "stdafx.h"
#include "PlayerStand.h"
#include "PlayerState.h"
#include "../Player.h"
#include "../../UI/WeaponSelect/WeaponSelect.h"
#include "../../Scene/SceneManager.h"
#include "../Weapon/WeaponManager.h"

void CPlayerStand::Init()
{
	//�ҋ@�A�j���[�V�����̍Đ�
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationStand, 0.5f);
	CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_pPlayerGetter->SetMoveSpeed(moveSpeed);
}

void CPlayerStand::Update()
{
	if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() != enPlayerAnimationStand)
	{
		if (!m_pPlayerGetter->GetAnimation().IsPlay())
		{
			m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationStand);
		}
		return;
	}
	//���S�����ꍇ�̏���
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDied))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDied);
	}
	//�_���[�W���󂯂��ꍇ�̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	//�U�����������̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
	}
	//�U�����������̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAttack);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateJump))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove)) 
	{
		//���C���[�ړ��ł���Ȃ�J��
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	//�ړ��̓��͂�����Ȃ�����A�j���[�V�����ɑJ��
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
	{
		//GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateWalk);
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateSky))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
	}
}
void CPlayerStand::ChangeWepon()
{
	
}
