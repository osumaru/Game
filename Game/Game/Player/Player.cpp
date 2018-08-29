#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"

void Player::Init(Vector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_position = position;
	m_characterController.Init(2.0f, 2.0f, m_position);
	m_characterController.SetGravity(-9.0f);
	wchar_t* animClip[2] = { L"Assets/modelData/unity2.tka", L"Assets/modelData/unity3.tka" };
	m_animation.Init(animClip, 2);

	//�v���C���[�̃X�e�[�^�X�̏�����
	{

		m_status.Strength	= 10;				//�U����
		m_status.Defense	= 3;				//�h���
		m_status.Health		= 100;				//�̗�
		m_status.Level		= 1;				//���x��
		m_status.OldExp		= 15;				//�ЂƂO�̃��x���ɕK�v�Ȍo���l
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l
		m_status.ExperiencePoint = 0;				//�o���l
		m_status.AccumulationExp += m_status.OldExp;	//�ݐόo���l
	}

	Add(this, 0);
}

void Player::Update()
{

	Move();					//�ړ�����
	Rotation();				//��]����
	//AnimationMove();		//�A�j���[�V�����̏���
	StatusCalculation();	//�X�e�[�^�X�̏���

	if (GetPad().IsTriggerButton(enButtonB))
	{
		m_status.ExperiencePoint += 43;
		m_status.AccumulationExp += 43;

	}

	//�X�L�����f���̍X�V
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);


}

void Player::Draw()
{
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void Player::Move()
{
	

		Vector3 moveSpeed;
		moveSpeed.z = GetPad().GetLeftStickY() * GetGameTime().GetDeltaFrameTime() * 5;
		moveSpeed.x = GetPad().GetLeftStickX() * GetGameTime().GetDeltaFrameTime() * 5;

		Matrix cameraVm = GetGameCamera().GetViewMatrix();
		cameraVm.Inverse();	//�J�����̃r���[�s��̋t�s��

		//�J�����̑O����
		Vector3 cameraZ;
		cameraZ.x = cameraVm.m[2][0];
		cameraZ.y = 0.0f;
		cameraZ.z = cameraVm.m[2][2];
		cameraZ.Normalize();

		//�J�����̉�����
		Vector3 cameraX;
		cameraX.x = cameraVm.m[0][0];
		cameraX.y = 0.0f;
		cameraX.z = cameraVm.m[0][2];
		cameraX.Normalize();

		//�L�����N�^�[���ړ������鏈��
		m_moveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
		m_moveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;

		if (GetPad().IsPressButton(enButtonRB))
		{
			m_moveSpeed *= 5;

		}

		m_characterController.SetMoveSpeed(m_moveSpeed);
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GetGameTime().GetDeltaFrameTime());

		m_position = m_characterController.GetPosition();

}

void Player::Rotation()
{

	Vector3 playerVec = m_moveSpeed;


	if (playerVec.LengthSq() > 0.001f)
	{


		Quaternion rot = Quaternion::Identity;
		rot.SetRotation(Vector3::AxisY, atan2f(playerVec.x, playerVec.z));		//Y������̉�]
		m_rotation.Slerp(0.02f, m_rotation, rot);


	}

}

void Player::AnimationMove()
{

	if (GetPad().IsTriggerButton(enButtonA))
	{
		m_animation.Play(0);
	}

	m_animation.Update(GetGameTime().GetDeltaFrameTime());

}

void Player::StatusCalculation()
{
	//���x���A�b�v�̏���
	if (m_status.NextExp <= m_status.ExperiencePoint)
	{
		m_status.ExperiencePoint -= m_status.NextExp;

		m_status.Level += 1;

		m_status.OldExp = m_status.NextExp;

		m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l

		//10���x�����Ƃ̃X�e�[�^�X�̏㏸��
		if (m_status.Level % 10 == 0)
		{

			m_status.Strength	+= 9;
			m_status.Defense	+= 6;
			m_status.Health		+= 25;


		}
		//�������x�����Ƃ̃X�e�[�^�X�̏㏸��
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.Health += 14;

		}

		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.Health += 11;
		}

	}


}