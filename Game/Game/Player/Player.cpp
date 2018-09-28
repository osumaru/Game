#include "stdafx.h"
#include "Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Map/Map.h"`
#include "../Scene/SceneManager.h"
#include "../Enemy/IEnemy.h"


void CPlayer::Init(CVector3 position)
{
	
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");
	//����̃��f���̃��[�h
	m_Weaponskin[0].Load(L"Assets/modelData/Sword.cmo", NULL);
	m_Weaponskin[1].Load(L"Assets/modelData/LargeSword.cmo", NULL);
	m_Weaponskin[2].Load(L"Assets/modelData/LongBow.cmo", NULL);
	m_Weaponskin[3].Load(L"Assets/modelData/TwinSword.cmo", NULL);

	m_position = position;
	m_characterController.Init(0.3f, 1.0f,m_position);
	m_characterController.SetGravity(-9.8f);
	//���C�g�̐ݒ�
	m_light.SetAmbientLight({ 0.5f,0.5f,0.5f,1.0f});
	m_light.SetDiffuseLight(0, { 1.0f,1.0f,1.0f,1.0f });
	/*m_light.SetDiffuseLightDir(0, { 0.0707f,0.0f,0.707f,1.0f });*/
	m_skinmodel.SetLight(m_light);

	m_weaponBoxCollider.Create({ 0.05f,0.4f,0.05f });
	SRigidBodyInfo rInfo;
	rInfo.collider = &m_weaponBoxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_weaponPosition;
	rInfo.rot = m_weaponRotation;

	m_weaponRigitBody.Create(rInfo);
	m_weaponRigitBody.SetPosition(m_weaponPosition);
	m_weaponRigitBody.SetRotation(m_weaponRotation);
	m_weaponRigitBody.PhysicsWorldRemoveRigidBody();
	

	//�A�j���[�V�����̏�����
	{
		wchar_t* animClip[enPlayerNum] = {
											{ L"Assets/modelData/PlayerStand.tka"},			//�ҋ@�A�j���[�V����	
											{ L"Assets/modelData/PlayerWalkStay.tka" },		//���s�A�j���[�V����
											{ L"Assets/modelData/PlayerDash60fps.tka" },	//���s�A�j���[�V����
											{ L"Assets/modelData/PlayerJump.tka" },			//�W�����v�A�j���[�V����
											{ L"Assets/modelData/PlayerAttack.tka" },		//�U���A�j���[�V����
											{ L"Assets/modelData/PlayerDamage.tka" },		//�_���[�W�A�j���[�V����
											{ L"Assets/modelData/PlayerKaihi.tka" }	,		//����A�N�V����
											{ L"Assets/modelData/PlayerDeath.tka" },		//���S�A�j���[�V����
											{ L"Assets/modelData/PlayerArrowAttack.tka" },	//�|�̍U���A�j���[�V����
											{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },	//�匕�̍U���A�j���[�V����
											{ L"Assets/modelData/PlayerTwinSwordAttack.tka" }	//�񓁗��̍U���A�j���[�V����
		};

		m_animation.Init(animClip, enPlayerNum);
		m_animation.SetLoopFlg(enPlayerStand, true);
		m_animation.SetLoopFlg(enPlayerWalk, true);
		m_animation.SetLoopFlg(enPlayerRun, true);

	}


	//�v���C���[�̃X�e�[�^�X�̏�����
	{
		m_status.Strength	= 10;						//�U����
		m_status.Defense	= 3;						//�h���
		m_status.Health		= 100;						//�̗�
		m_status.MaxHealth = m_status.Health;			//���x�����Ƃ̍ő�HP
		m_status.Level		= 1;						//���x��
		m_status.OldExp		= 15;						//�ЂƂO�̃��x���ɕK�v�Ȍo���l
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l
		m_status.ExperiencePoint = 0;					//�o���l
		m_status.AccumulationExp += m_status.OldExp;	//�ݐόo���l
		m_status.Gold = 0;								//������
	}
	m_PlayerStateMachine.Start();
	m_PlayerRotation.Start();
	Add(&m_PlayerStateMachine,0);
	Add(&m_PlayerRotation, 0);
	Add(this, 1);
}

void CPlayer::Update()
{
	
	//�A�j���[�V�����̍X�V
	m_animation.Update(GameTime().GetDeltaFrameTime());
	if (m_isDied) { return; }
	WeaponChange();
	Move();					//�ړ�����
	StatusCalculation();	//�X�e�[�^�X�̏���
	PlayerAttack();

	if (Pad().IsTriggerButton(enButtonB))
	{
		ExpUP(100);	

	}
	
		//�X�L�����f���̍X�V
		m_Weaponskin[m_weaponState].Update(m_weaponPosition, m_weaponRotation, { 1.0f, 1.0f, 1.0f }, true);
		m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);		

}

//�`�揈��
void CPlayer::Draw()
{

	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	if (m_isAttack)
	{
		CVector3 weponUpVec = { m_Weaponskin[m_weaponState].GetWorldMatrix().m[2][0],m_Weaponskin[m_weaponState].GetWorldMatrix().m[2][1],m_Weaponskin[m_weaponState].GetWorldMatrix().m[2][2] };
		weponUpVec *= 0.7f;
		m_weaponPosition.Add(weponUpVec);
		m_weaponRigitBody.SetPosition(m_weaponPosition);
		m_weaponRigitBody.SetRotation(m_weaponRotation);
		m_Weaponskin[m_weaponState].Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());

	}

	m_Weaponskin[m_weaponState].Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	
}

void CPlayer::Move()
{

		m_moveSpeed = m_characterController.GetMoveSpeed();

		//�ړ����Ă���Ƃ��̏���
		if (m_State == enPlayerWalk || m_State == enPlayerRun)
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
			m_moveSpeed.z = cameraX.z * moveSpeed.x + cameraZ.z * moveSpeed.z;


			//�_�b�V���̏���
			if (Pad().IsPressButton(enButtonRB))
			{

				m_moveSpeed.x *= RUN_SPEED;
				m_moveSpeed.z *= RUN_SPEED;
			}

			
		}
		//�W�����v���̈ړ�����
		else if (Pad().IsTriggerButton(enButtonA))
		{

			m_moveSpeed.y = 10.0f;
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}
		//�ҋ@��Ԃ�U�����̏���
		else 
		{

			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}

		//����A�N�V�������̏���
		if (m_State == enPlayerAvoidance)
		{

			CMatrix PlayerHip = m_skinmodel.FindBoneWorldMatrix(L"Hips");
			CVector3 PlayerHipPos = { PlayerHip.m[3][0],0.0,PlayerHip.m[3][2] };
	
		
		}

		if (m_State != enPlayerAvoidance)
		{

			m_characterController.SetMoveSpeed(m_moveSpeed);
			m_characterController.SetPosition(m_position);
			m_characterController.Execute(GameTime().GetDeltaFrameTime());
			m_position = m_characterController.GetPosition();


		}


}

//�v���C���[�̉�]���s���֐�

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
			m_status.MaxHealth	+= 25;
			m_status.Health = m_status.MaxHealth;


		}
		//�������x�����Ƃ̃X�e�[�^�X�̏㏸��
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.MaxHealth += 14;
			m_status.Health = m_status.MaxHealth;


		}

		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.MaxHealth += 11;
			m_status.Health = m_status.MaxHealth;
		}

	}


}

void  CPlayer::WeaponChange()
{
	if (m_weaponState == (EnPlayerWeapon)GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon()) { return; }
	m_weaponState = (EnPlayerWeapon)GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon();
	switch (m_weaponState)
	{
		//�Ў茕�̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
		break;
		//�|�̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enBow:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerArroAttack);
		break;
		//�匕�̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enLargeSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerLongSwordAttack);
		break;
		//�o���̎��̍U�����[�V�����̐ݒ�
	case CWeaponSelect::enTwinSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerTwinSwordAttack);
		break;
	}
}

void CPlayer::PlayerAttack()
{
	if (!m_isAttack) { return; }
	int num = 0;
	
	//�G�l�~�[�̃��X�g���擾
	for (const auto& enemys : GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
	{
		if (!enemys->IsDamage()) {

			CVector3 EnemyVec = enemys->GetPosition();
			EnemyVec.y += 1.3f;
			EnemyVec -= m_weaponPosition;
			float len = EnemyVec.Length();

			if (fabs(len) < 2.0f)
			{
				enemys->SetIsDamage(true);
			}

		}
	}
	

}