#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "PlayerSate/PlayerState.h"
#include "../Camera/GameCamera.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"


CPlayerMove::CPlayerMove()
{
}


CPlayerMove::~CPlayerMove()
{
}

bool CPlayerMove::Start()
{

	return true;
}

void CPlayerMove::Update()
{
	//�v���C���[�̑��x���擾
	m_PlayerMoveSpeed = GetPlayer().GetMoveSpeed();

	//�_���[�W���󂯂Ă���Ƃ��͈ړ����Ȃ�
	//�v���C���[���󒆂ɂ��鎞���ړ������Ȃ�
	//�U�������ړ������Ȃ�
	if (
		GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerDamage ||
		GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAttack
		)
	{
		
		m_PlayerMoveSpeed.x = 0.0f;
		m_PlayerMoveSpeed.z = 0.0f;
	}

	//��𒆂̈ړ�����
	else if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAvoidance)
	{
		m_PlayerMoveSpeed = {0.0f, 0.0f, 0.0f};
		////�v���C���[�̃��[���h�s��̎擾
		CMatrix PlayerWorldMatrix = GetPlayer().GetPlayerSkin().GetWorldMatrix();
		////�v���C���[�̑O�����̎擾
		CVector3 PlayerFront = { PlayerWorldMatrix.m[1][0],PlayerWorldMatrix.m[1][1],PlayerWorldMatrix.m[1][2] };
		PlayerFront.Normalize();
		PlayerFront *= 300.0f;
		CVector3 OneVec = CVector3::One;
		if (m_PlayerMoveSpeed.Length() == 0)
		{
			m_PlayerMoveSpeed -= PlayerFront * GameTime().GetDeltaFrameTime();
		}
		else
		{

			m_PlayerMoveSpeed -= m_PlayerMoveSpeed * GameTime().GetDeltaFrameTime();

		}

	}
	else if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::enPlayerWireMove)
	{

	}
	//�ړ��̓��͂����邩�̔���
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
	{
		CVector3 moveSpeed;
		//1�t���[���ɐi�ދ���
		moveSpeed.z = Pad().GetLeftStickY() * WALK_SPEED;
		moveSpeed.x = Pad().GetLeftStickX() * WALK_SPEED;
		CMatrix cameraVm = GetGameCamera().GetViewMatrix();
		cameraVm.Inverse();	//�J�����̃r���[�s��̋t�s��

		//�J�����̑O����
		CVector3 cameraZ;
		cameraZ.x = cameraVm.m[2][0];
		cameraZ.y = 0.0f;
		cameraZ.z = cameraVm.m[2][2];
		cameraZ.Normalize();

		//�J�����̉�����
		CVector3 cameraX;
		cameraX.x = cameraVm.m[0][0];
		cameraX.y = 0.0f;
		cameraX.z = cameraVm.m[0][2];
		cameraX.Normalize();


		//�L�����N�^�[���ړ������鏈��
		m_PlayerMoveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
		m_PlayerMoveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;

		//�_�b�V���̏���
		if (Pad().IsPressButton(enButtonRB))
		{

			m_PlayerMoveSpeed.x *= RUN_SPEED;
			m_PlayerMoveSpeed.z *= RUN_SPEED;
		}


		if (Pad().IsTriggerButton(enButtonA))
		{
			if (GetPlayer().GetPlayerStateMachine().GetState() != CPlayerState::EnPlayerState::enPlayerRunJump)
			{

				m_PlayerMoveSpeed.y += 5.0f;
			}
		}
	}


		
	//�����A�j���[�V�����̏���
	else
	{
		m_PlayerMoveSpeed.x = 0.0f;
		m_PlayerMoveSpeed.z = 0.0f;
	
	}

	//�L�����N�^�[�R���g���[���[�̃A�b�v�f�[�g����
	{
		GetPlayer().GetCharacterController().SetPosition(GetPlayer().GetPosition());
		GetPlayer().GetCharacterController().SetMoveSpeed(m_PlayerMoveSpeed);
		GetPlayer().GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

		GetPlayer().SetPosition(GetPlayer().GetCharacterController().GetPosition());
		GetPlayer().SetMoveSpeed(GetPlayer().GetCharacterController().GetMoveSpeed());
	}
}
