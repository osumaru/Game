#include "stdafx.h"
#include "Player.h"
#include "../GameCamera.h"
#include "../Map/Map.h"

void CPlayer::Init(CVector3 position)
{
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_Weaponskin.Load(L"Assets/modelData/Sword.cmo", NULL);
	m_position = position;
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);
	m_characterController.Init(0.6f, 4.0f,m_position);
	m_characterController.SetGravity(-9.8f);
	wchar_t* animClip[enPlayerNum] = {	{ L"Assets/modelData/PlayerStand.tka"},			//�ҋ@�A�j���[�V����	
										{ L"Assets/modelData/PlayerWalkStay.tka" },		//���s�A�j���[�V����
										{ L"Assets/modelData/PlayerDashStay.tka" },		//���s�A�j���[�V����
										{ L"Assets/modelData/PlayerJump.tka" },			//�W�����v�A�j���[�V����
										{ L"Assets/modelData/PlayerAttack.tka" },		//�U���A�j���[�V����
										{ L"Assets/modelData/PlayerDamage.tka" },		//�_���[�W�A�j���[�V����
										{  L"Assets/modelData/PlayerKaihi.tka" }
									 };
	m_animation.Init(animClip, enPlayerNum);
	m_animation.SetLoopFlg(0, true);
	m_animation.SetLoopFlg(1, false);

	//�v���C���[�̃X�e�[�^�X�̏�����
	{

		m_status.Strength	= 10;						//�U����
		m_status.Defense	= 3;						//�h���
		m_status.Health		= 100;						//�̗�
		m_status.Level		= 1;						//���x��
		m_status.OldExp		= 15;						//�ЂƂO�̃��x���ɕK�v�Ȍo���l
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l
		m_status.ExperiencePoint = 0;					//�o���l
		m_status.AccumulationExp += m_status.OldExp;	//�ݐόo���l
	}

	Add(this, 0);
}

void CPlayer::Update()
{

	AnimationMove();		//�A�j���[�V�����̏���
	Move();					//�ړ�����
	Rotation();				//��]����
	StatusCalculation();	//�X�e�[�^�X�̏���

	if (Pad().IsTriggerButton(enButtonB))
	{
		m_status.ExperiencePoint += 43;
		m_status.AccumulationExp += 43;
		
	}


	//�X�L�����f���̍X�V
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_Weaponskin.Update(m_WeaponPosition, m_WeaponRotation, { 1.0f, 1.0f, 1.0f }, true);
	
}

//�`�揈��
void CPlayer::Draw()
{
	//m_characterController.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	if (m_animation.GetCurrentAnimationNum() == enPlayerAtack)
	{

		m_Weaponskin.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());

	}
	
}

void CPlayer::Move()
{
		m_moveSpeed = m_characterController.GetMoveSpeed();

		//�ړ����Ă��邩�̔���
		if (m_State != enPlayerStand)
		{


			CVector3 moveSpeed;
			moveSpeed.z = Pad().GetLeftStickY() * GameTime().GetDeltaFrameTime() * WALK_SPEED;
			moveSpeed.x = Pad().GetLeftStickX() * GameTime().GetDeltaFrameTime() * WALK_SPEED;

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
			m_moveSpeed.x = cameraX.x * moveSpeed.x + cameraZ.x * moveSpeed.z;
			//m_moveSpeed.y = 0;
			m_moveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;


			//�_�b�V���̏���
			if (Pad().IsPressButton(enButtonRB))
			{

				m_moveSpeed.x *= RUN_SPEED;
				m_moveSpeed.z *= RUN_SPEED;
			}

			else if (m_State == enPlayerJump)
			{

				m_moveSpeed.y = 1.0f;
			}


			//����̏���
			if (Pad().IsTriggerButton(enButtonRightTrigger))
			{
				m_isSlip = true;
			}

			if (m_isSlip)
			{
				m_slipSpeed = m_slipSpeed - (60.0f * GameTime().GetDeltaFrameTime());
				if (m_slipSpeed <= 0)
				{
					m_isSlip = false;
					m_slipSpeed = 15.0f;
					return;
				}
				CVector3 playerFlontVec = { m_skinmodel.GetWorldMatrix().m[2][0],0.0f,m_skinmodel.GetWorldMatrix().m[2][2] };
				playerFlontVec.Normalize();
				m_moveSpeed = playerFlontVec * m_slipSpeed;
			}

		}

		else
		{

			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}


	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

}

//�v���C���[�̉�]���s���֐�
void CPlayer::Rotation()
{

	CVector3 playerVec = m_moveSpeed; //
	playerVec.y = 0.0f;

	//�v���C���[�̎�̃{�[�����擾
	{
		CMatrix PlayerHnd = m_skinmodel.FindBoneWorldMatrix(L"LeftHandMiddle1");

		CVector3 PlayerHndPos = { PlayerHnd.m[3][0],PlayerHnd.m[3][1],PlayerHnd.m[3][2] };

		CVector3 PlayerHndScale = { PlayerHnd.m[0][0], PlayerHnd.m[0][1], PlayerHnd.m[0][2] };
		float len = PlayerHndScale.Length();
		PlayerHnd.m[0][0] /= len;
		PlayerHnd.m[0][1] /= len;
		PlayerHnd.m[0][2] /= len;

		PlayerHnd.m[1][0] /= len;
		PlayerHnd.m[1][1] /= len;
		PlayerHnd.m[1][2] /= len;

		PlayerHnd.m[2][0] /= len;
		PlayerHnd.m[2][1] /= len;
		PlayerHnd.m[2][2] /= len;


		m_WeaponPosition = PlayerHndPos;
		m_WeaponRotation.SetRotation(PlayerHnd);
	}

	//�v���C���[�̉�]�̏���
	if (playerVec.LengthSq() > 0.001f)
	{


		CQuaternion rot = CQuaternion::Identity;
		rot.SetRotation(CVector3::AxisY, atan2f(playerVec.x, playerVec.z));		//Y������̉�]
		m_rotation.Slerp(0.2f, m_rotation, rot);


	}


}

void CPlayer::AnimationMove()
{
	//�U���A�j���[�V�����̏���
	if (Pad().IsTriggerButton(enButtonX) && m_animation.GetCurrentAnimationNum() != enPlayerAtack)
	{
		m_animation.Play(enPlayerAtack, 0.5f);
		m_State = enPlayerAtack;
	}

	//����A�j���[�V����
	else if (Pad().IsTriggerButton(enButtonRightTrigger))
	{

		m_animation.Play(enPlayerAvoidance, 0.5f);
	}

	//�W�����v�A�j���[�V�����̏���
	else if (Pad().IsTriggerButton(enButtonY) && m_animation.GetCurrentAnimationNum() != enPlayerJump)
	{
		m_animation.Play(enPlayerJump, 0.5);
		m_State = enPlayerJump;

	}

	

	//�ړ��A�j���[�V�����̏���
	else if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0 )
	{
		m_animation.SetLoopFlg(enPlayerRun, true);
		m_animation.SetLoopFlg(enPlayerWalk, true);
		CVector3 moveLen = m_characterController.GetMoveSpeed();
		
		float len = moveLen.Length();
		if (len < 0.0)
		{
			len *= -1.0f;
		}
	
	//���s�A�j���[�V����
	 if (len < 2.0f &&m_animation.GetCurrentAnimationNum() != enPlayerWalk)
		{


			m_animation.Play(enPlayerWalk, 0.2);
			m_State = enPlayerWalk;

		}
	 //����A�j���[�V����
	 else if (len >= 2.0f && m_animation.GetCurrentAnimationNum() != enPlayerRun)
	 {

		 m_animation.Play(enPlayerRun, 0.5);
		 m_State = enPlayerRun;

	 }
	}
	
	//�ҋ@���[�V����
	if (m_animation.GetCurrentAnimationNum() != 0 && Pad().GetLeftStickX() == 0 && Pad().GetLeftStickY() == 0)
	{
		m_animation.SetLoopFlg(1, false);
		if (!m_animation.IsPlay() || m_animation.GetCurrentAnimationNum() == enPlayerRun ||  m_animation.GetCurrentAnimationNum() == enPlayerWalk)
		{

			m_animation.Play(enPlayerStand, 0.2f);
			m_State = enPlayerStand;

		}

	}

	m_animation.Update(GameTime().GetDeltaFrameTime());

}

void CPlayer::StatusCalculation()
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

void  CPlayer::WeaponChange()
{



}