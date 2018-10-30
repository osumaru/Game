#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CPlayerRun::Init()
{
	m_pPlayer->SetPlayerAnimation(CPlayerState::enPlayerRun, 0.2f);
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
	CVector3 moveSpeed = m_pPlayer->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	const float speed = 4.0f;
	moveSpeed += frontVec * Pad().GetLeftStickY() * speed;
	moveSpeed += rightVec * Pad().GetLeftStickX() * speed;
	m_pPlayer->SetMoveSpeed(moveSpeed);

	//���蒆�Ƀ_���[�W���󂯂��ꍇ
	if (m_pPlayer->GetIsDamage())
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerDamage);
	}
	//�����Ă���Ƃ��ɍU���������̏���
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{
		if(m_pPlayer->GetWeapon().GetCurrentState() == CWeapon::enWeaponArrow)
		{
			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerArrowAttack);
		}
		else
		{

			m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerAttack);
		}
	}
	//���蒆�ɉ���������̏���
	else if (Pad().IsTriggerButton(enButtonB))
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerAvoidance);
	}
	//�����Ă��鎞�ɃW�����v�������ꂽ�Ƃ�����
	else if (Pad().IsTriggerButton(enButtonA))
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerRunJump);
	}

	else if (fabs(m_pPlayer->GetMoveSpeed().Length()) == 0.0f)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStand);
	}
	else if (m_pPlayer->IsWireMove())
	{
		//���C���[�ړ��ł���Ȃ�J��
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerWireMove);
	}
}