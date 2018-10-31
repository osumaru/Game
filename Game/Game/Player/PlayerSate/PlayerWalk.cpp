#include "stdafx.h"
#include "PlayerWalk.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"


void CPlayerWalk::Init()
{
	//�����A�j���[�V�����̍Đ�
	m_pPlayer->PlayAnimation(enPlayerAnimationWalk, 0.2f);
}

void CPlayerWalk::Update()
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

	//�ړ��̓��͂��Ȃ���Αҋ@�A�j���[�V�����ɑJ��
	if (Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}

	else if (Pad().IsTriggerButton(enButtonA))
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateJump);
	}

	//���ȏ�̑����Ȃ炠�m��A�j���[�V�����ɑJ��
	else if (fabs(m_pPlayer->GetMoveSpeed().Length()) >= 1.3f)
	{
		m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateRun);
	}

}
