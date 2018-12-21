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
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	//�����Ă���Ƃ��ɍU���������̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
	}
	//�����Ă���Ƃ��ɍU���������̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAttack);
	}
	//���蒆�ɉ���������̏���
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	//�����Ă��鎞�ɃW�����v�������ꂽ�Ƃ�����
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRunJump))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRunJump);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStand))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove))
	{
		//���C���[�ړ��ł���Ȃ�J��
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	/*else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateSky))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
	}*/
}