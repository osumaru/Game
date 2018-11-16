#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CPlayerRun::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationRun, 0.2f);
}

void CPlayerRun::Update()
{
	const CCamera& gameCamera = GetGameCamera().GetCamera();
	CVector3 frontVec = gameCamera.GetTarget() - gameCamera.GetPosition();
	frontVec.y = 0.0f;
	frontVec.Normalize();
	CVector3 rightVec;
	rightVec.Cross(CVector3::AxisY, frontVec);
	rightVec.Normalize();
	CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	const float speed = 8.0f;
	moveSpeed += frontVec * Pad().GetLeftStickY() * speed;
	moveSpeed += rightVec * Pad().GetLeftStickX() * speed;
	m_pPlayerGetter->SetMoveSpeed(moveSpeed);
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	//���蒆�Ƀ_���[�W���󂯂��ꍇ
	if (m_pPlayer->GetIsDamage())
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	//�����Ă���Ƃ��ɍU���������̏���
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if(m_pPlayer->GetWeaponManager().GetCurrentState() == CWeaponManager::enArrow)
		{
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
		}
		else
		{

			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAttack);
		}
	}
	//���蒆�ɉ���������̏���
	else if (Pad().IsTriggerButton(enButtonB))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	//�����Ă��鎞�ɃW�����v�������ꂽ�Ƃ�����
	else if (Pad().IsTriggerButton(enButtonA))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRunJump);
	}

	else if (fabs(m_pPlayerGetter->GetMoveSpeed().Length()) == 0.0f)
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
	else if (m_pPlayer->GetWireAction().IsWireMove())
	{
		//���C���[�ړ��ł���Ȃ�J��
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
}