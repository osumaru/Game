#include "stdafx.h"
#include "Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Map/Map.h"
#include "../Scene/SceneManager.h"
#include "../Enemy/IEnemy.h"
#include "../Item/IItem.h"
#include "../UI/Menu/ItemInventory.h"
#include "../UI/Menu/EquipInventory.h"
#include "../Enemy/Maw.h"
#include "Weapon/Bow.h"
#include "../Enemy/PathFinding/PathFinding.h"

CPlayer *CPlayer::m_player = NULL;
SplayerStatus CPlayer::m_status = {
	m_status.Strength = 10,							//�U����
	m_status.Defense = 3,							//�h���
	m_status.Health = 100,							//�̗�
	m_status.MaxHealth = m_status.Health,			//���x�����Ƃ̍ő�HP
	m_status.Level = 1,								//���x��
	m_status.OldExp = 15,							//�ЂƂO�̃��x���ɕK�v�Ȍo���l
	m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5,	//���̃��x���A�b�v�ɕK�v�Ȍo���l
	m_status.ExperiencePoint = 0,					//�o���l
	m_status.AccumulationExp += m_status.OldExp,	//�ݐόo���l
	m_status.Gold = 4000,							//������
};

void CPlayer::OnInvokeAnimationEvent(//�A�j���[�V�����C�x���g���Ă΂�邲�ƂɌĂяo�����H
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{

	if (wcscmp(animClipName, L"Assets/modelData/PlayerDash60fpsEvent.tka") == 0)
	{//�C�x���g���ŏ�����ς���H
		const float footVolume = 0.1f;
		CSoundSource* footSound = New<CSoundSource>(0);
		footSound->Init("Assets/sound/SystemSound/Run.wav");
		footSound->Play(false);
		footSound->SetVolume(footVolume);
	}

	if (wcscmp(animClipName, L"Assets/modelData/PlayerThrustAttack.tka") == 0)
	{//���Ԃ�Ă΂ꂽ
		/*
		auto soundSource = New<CSoundSource>(0);
		soundSource->Init("sound/Footstep_00.wav");
		soundSource->Play(false);
		*/
	}

	if (!wcscmp(animClipName, L"Assets/modelData/PlayerLeageAttackFirst.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerLeageAttackSecand.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerLeageAttackThird.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerTwinAttackFirst.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerTwinAttackSecand.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerTwinAttackThird.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerCombo4.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerCombo5.tka") || 
		!wcscmp(animClipName, L"Assets/modelData/PlayerCombo6.tka"))
	{
		m_weaponManager.SetIsAttackCheck(!m_weaponManager.GetIsAttackCheck());
	}
}

void CPlayer::BeforeDead()
{
	((CBow*)m_weaponManager.GetWeapon(enWeaponArrow))->Release();
}

void CPlayer::Init(CVector3 position)
{
	//Sleep(10000);
	//�v���C���[�̃X�L�������f���̃��[�h
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");

	m_position = position;
	m_skinmodel.Update(m_position, CQuaternion::Identity, CVector3::One);

	m_characterController.Init(0.4f, 1.1f, m_position);
	m_characterController.SetGravity(-30.0f);
	m_characterController.SetUserIndex(enCollisionAttr_Player);

	//�A�j���[�V�����̏�����
	{
		wchar_t* animClip[enPlayerAnimationNum] = {
									{ L"Assets/modelData/PlayerStand.tka"},					//�ҋ@�A�j���[�V����	
									{ L"Assets/modelData/PlayerWalkStay.tka" },				//���s�A�j���[�V����
									{ L"Assets/modelData/PlayerDash60fpsEvent.tka" },		//����A�j���[�V����
									{ L"Assets/modelData/PlayerDashDash.tka" },				//�_�b�V���A�j���[�V����
									{ L"Assets/modelData/PlayerRunJump.tka" },				//����W�����v�A�j���[�V����
									{ L"Assets/modelData/PlayerJump2.tka" },				//�W�����v�A�j���[�V����
									{ L"Assets/modelData/PlayerCombo4.tka" },				//�U���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo5.tka" },				//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo6.tka" },				//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo4Combine.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo5Combine.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo6Combine.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerLeageAttackFirst.tka" },		//�U���A�j���[�V����
									{ L"Assets/modelData/PlayerLeageAttackSecand.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerLeageAttackThird.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerLeageAttackFirstEnd.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerLeageAttackSecandEnd.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerLeageAttackThirdEnd.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinAttackFirst.tka" },		//�U���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinAttackSecand.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinAttackThird.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinAttackFirstEnd.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinAttackSecandEnd.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinAttackThirdEnd.tka" },	//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerJumpAttack.tka"},			//�W�����v�U���A�j���[�V����
									{ L"Assets/modelData/PlayerStun.tka" },					//�X�^���A�j���[�V����
									{ L"Assets/modelData/PlayerDamage.tka" },				//�_���[�W�A�j���[�V����
									{ L"Assets/modelData/PlayerJumpDamage.tka"},			//�_���[�W(��)�A�j���[�V����
									{ L"Assets/modelData/PlayerRoll.tka" }	,				//����A�N�V����
									{ L"Assets/modelData/PlayerRollCombine.tka" }	,		//����A�N�V����
									{ L"Assets/modelData/PlayerDeath.tka" },				//���S�A�j���[�V����
									{ L"Assets/modelData/PlayerWireThrow2.tka"},			//���C���[�𓊂���A�j���[�V����
									{ L"Assets/modelData/PlayerWireMove.tka" },				//���C���[�ړ��A�j���[�V����
									{ L"Assets/modelData/PlayerJumpTackle.tka"},			//���C���[�U���A�j���[�V����
									{ L"Assets/modelData/PlayerArrowAttack.tka" },			//�|�̍U���A�j���[�V����
									{ L"Assets/modelData/PlayerArrowAttackEvent.tka" },
									{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },		//�匕�̍U���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinSwordAttack.tka" },		//�񓁗��̍U���A�j���[�V����
									{ L"Assets/modelData/PlayerLanding.tka" },				//���n�A�j���[�V����
									{ L"Assets/modelData/PlayerDown.tka" },					//�_�E���A�j���[�V����
									{ L"Assets/modelData/PlayerUp.tka" }					//�N���オ��A�j���[�V����
		};

		m_animation.Init(animClip, enPlayerAnimationNum);
		m_animation.SetLoopFlg(enPlayerAnimationStand, true);
		m_animation.SetLoopFlg(enPlayerAnimationWalk, true);
		m_animation.SetLoopFlg(enPlayerAnimationRun, true);
		m_animation.SetLoopFlg(enPlayerAnimationDash, true);
		m_animation.SetLoopFlg(enPlayerAnimationWireMove, true);

		//�A�j���[�V�����C�x���g���X�i�[�̓o�^�@�Ăяo�����֐��̓o�^�H
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
		{
			OnInvokeAnimationEvent(animClipname, eventName);
		});
	}

	//�v���C���[�̃X�e�[�^�X�̏�����
	{
	m_status.Health = m_status.MaxHealth;
	m_status.MaxHealth = m_status.MaxHealth;
	//	m_status.Strength = 10;							//�U����
	//	m_status.Defense = 3;							//�h���
	//	m_status.Health = 100;							//�̗�
	//	m_status.MaxHealth = m_status.Health;			//���x�����Ƃ̍ő�HP
	//	m_status.Level = 1;								//���x��
	//	m_status.OldExp = 15;							//�ЂƂO�̃��x���ɕK�v�Ȍo���l
	//	m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;	//���̃��x���A�b�v�ɕK�v�Ȍo���l
	//	m_status.ExperiencePoint = 0;					//�o���l
	//	m_status.AccumulationExp += m_status.OldExp;	//�ݐόo���l
	//	m_status.Gold = 4000;							//������
	}
	m_playerGetter.SetPlayer(this);

	CVector3 boxSize = { 0.4f,0.6f,0.4f };
	m_boxCollider.Create({ boxSize.x,boxSize.y,boxSize.z });
	m_groundCollision.Init(&m_boxCollider,m_position, CQuaternion::Identity);
	CVector3 manipVector = { 0.0f,0.0f,100.0f };
	CVector3 oldRigidPos = m_characterController.GetPosition();
	m_characterController.SetPosition(manipVector);
	m_groundCollision.Execute();
	m_characterController.SetPosition(oldRigidPos);
	m_PlayerStateMachine.SetPlayer(this, &m_playerGetter);
	m_PlayerStateMachine.Init();
	m_skinmodel.SetIsShadowCaster(true);
	m_weaponManager.Init(this);
	m_wireAction.Init(this);
	SetIsActive(true);
	GetGameCamera().CameraSetPlayer();
	m_wireDraw.Init(CVector3::Zero, CVector3::Zero, CVector3::Zero);

}

void CPlayer::Update()
{
	m_position = m_characterController.GetPosition();
	if (m_isDied)
	{
		return;
	}

	StatusCalculation();	//�X�e�[�^�X�̏���

	float stickX = Pad().GetLeftStickX();
	float stickZ = Pad().GetLeftStickY();
	CVector3 stickDir = { stickX, 0.0f, stickZ };
	m_playerGetter.SetStickDir(stickDir);

	/*if (Pad().IsPressButton(enButtonX))
	{
		m_status.Health = 0;
	}*/

	if (Pad().IsTriggerButton(enButtonB))
	{
		m_isDamege = true;
	}

	CMatrix viewMat;
	CVector3 cameraPos = m_position;
	cameraPos.y += 50.0f;
	CVector3 shadowCameraUp = GetGameCamera().GetSpringCamera().GetTarget() - GetGameCamera().GetSpringCamera().GetPosition();
	shadowCameraUp.y = 0.0f;
	shadowCameraUp.Normalize();
	viewMat.MakeLookAt(cameraPos, m_position, CVector3::AxisX);
	CMatrix projMat;
	projMat.MakeOrthoProjectionMatrix(5, 5, 1.0f, 1000.0f);
	Engine().GetShadowMap().SetViewMatrix(viewMat);
	Engine().GetShadowMap().SetProjectionMatrix(projMat);
	m_wireAction.Update();
	Rotation(m_characterController.GetMoveSpeed());
	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_PlayerStateMachine.Update();
	m_isAction = true;
	m_animation.Update(0.0f);
	m_position = m_characterController.GetPosition();

	//�A�j���[�V�����̍X�V
	//�X�L�����f���̍X�V
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_weaponManager.Update();
	//�␳�l�������č��̂����炷
	CVector3 manipVector = { 0.0f,0.0f,100.0f };
	CVector3 oldRigidPos = m_characterController.GetPosition();
	m_characterController.SetPosition(manipVector);
	m_groundCollision.SetPosition(m_position);
	m_groundCollision.Execute();
	m_characterController.SetPosition(oldRigidPos);
}

//�`�揈��
void CPlayer::Draw()
{
	//g_pathFinding.GetNavigationMesh().Draw();
	m_characterController.Draw();
	m_weaponManager.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CPlayer::AfterDraw()
{
	m_weaponManager.AfterDraw();
	if (m_wireAction.IsWireMove()) 
	{
		m_wireDraw.Draw();
	}
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

			m_status.Strength += 9;
			m_status.Defense += 6;
			m_status.MaxHealth += 25;
		}
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.MaxHealth += 14;
		}
		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.MaxHealth += 11;
		}

		m_status.Health = m_status.MaxHealth;
	}
}



void CPlayer::Rotation(const CVector3& stickDir)
{
	if (m_isDamege) {
		return;
	}

	CVector3 moveSpeed = stickDir;
	CVector3 playerFront = CVector3::Front;
	if (moveSpeed.x == 0.0f && moveSpeed.z == 0.0f)
	{
		moveSpeed.x = m_skinmodel.GetWorldMatrix().m[2][0];
		moveSpeed.z = m_skinmodel.GetWorldMatrix().m[2][2];
	}
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();
	float rad = moveSpeed.Dot(playerFront);
	if (1.0f <= rad)
	{
		rad = 1.0f;
	}
	if (rad <= -1.0f)
	{
		rad = -1.0f;
	}
	rad = acosf(rad);
	CVector3 judgeAxis;
	judgeAxis.Cross(moveSpeed, playerFront);
	if (0.0f < judgeAxis.y)
	{
		rad = -rad;
	}
	CQuaternion addRot;
	addRot.SetRotation(CVector3::AxisY, rad);
	m_rotation.Slerp(0.3f , m_rotation, addRot);

	if (m_weaponManager.GetCurrentState() == enWeaponArrow && m_weaponManager.GetIsAttack())
	{
		CQuaternion rotXZ, rotY;
		CVector3 cameraFlont = GetGameCamera().GetCamera().GetFlont();
		cameraFlont.Normalize();
		rotXZ.SetRotation(CVector3::AxisY, atan2f(cameraFlont.x, cameraFlont.z));
		rotY.SetRotation(CVector3::AxisX, atanf(-cameraFlont.y));
		rotXZ.Multiply(rotY);
		m_rotation = rotXZ;
	}
	else if (m_wireAction.IsWireMove())
	{
		CVector3 moveSpeed = m_wireAction.GetWirePosition() - m_position;
		CVector3 moveSpeedXZ = moveSpeed;
		moveSpeedXZ.y = 0.0f;
		moveSpeed.Normalize();
		moveSpeedXZ.Normalize();
		rad = moveSpeedXZ.Dot(CVector3::Front);
		if (1.0f <= rad)
		{
			rad = 1.0f;
		}
		if (rad <= -1.0f)
		{
			rad = -1.0f;
		}
		rad = acosf(rad);
		CVector3 judgeAxis;
		judgeAxis.Cross(moveSpeedXZ, CVector3::Front);
		if (0.0f < judgeAxis.y)
		{
			rad = -rad;
		}
		CQuaternion multiY;
		multiY.SetRotation(CVector3::AxisY, rad);
		rad = moveSpeed.Dot(moveSpeedXZ);
		if (1.0f <= rad)
		{
			rad = 1.0f;
		}
		if (rad <= -1.0f)
		{
			rad = -1.0f;
		}
		rad = acosf(rad);
		if (moveSpeed.y > 0.0f)
		{
			rad = -rad;
		}
		CQuaternion multiX;
		multiX.SetRotation(CVector3::AxisX, rad);
		m_rotation = CQuaternion::Identity;
		m_rotation.Multiply(multiY);
		m_rotation.Multiply(multiX);
	}
}

bool CPlayer::GetIsStateCondition(CPlayerState::EnPlayerState state)
{
	switch (state)
	{
	case CPlayerState::enPlayerStateRun://���X�e�B�b�N�̓��͂���������
		return Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0;

	case CPlayerState::enPlayerStateArrowAttack://x�{�^���������đ������Ă��镐�킪�|��������
		return Pad().IsTriggerButton(enButtonX) && m_weaponManager.GetCurrentState() == enWeaponArrow;

	case CPlayerState::enPlayerStateArrowShoot:
		return !dynamic_cast<CPlayerArrowAttack*>(m_PlayerStateMachine.GetState(CPlayerState::enPlayerStateArrowAttack))->IsCharge();

	case CPlayerState::enPlayerStateAttack://x�{�^���������đ������Ă��镐�킪�|����Ȃ�������
		return Pad().IsTriggerButton(enButtonX) && m_weaponManager.GetCurrentState() != enWeaponArrow;

	case CPlayerState::enPlayerStateAvoidance://b�{�^���������Ă��邩
		return m_isAction && Pad().IsTriggerButton(enButtonB);

	case CPlayerState::enPlayerStateDamage://�_���[�W�t���O�������Ă��邩
		return m_isDamege;

	case CPlayerState::enPlayerStateDied://HP��0�ȉ���
		return m_status.Health <= 0;

	case CPlayerState::enPlayerStateJump://A�{�^���������Ă��邩
		return m_isAction && Pad().IsTriggerButton(enButtonA);

	case CPlayerState::enPlayerStateRunJump://A�{�^���������Ă��邩
		return m_isAction && Pad().IsTriggerButton(enButtonA);

	case CPlayerState::enPlayerStateWireMove://���C���[�ňړ�����t���O�������Ă��邩
		return m_wireAction.IsWireMove();

	case CPlayerState::enPlayerStateStand://�ړ��ʂ�0��
		return m_characterController.GetMoveSpeed().Length() == 0.0f;
	case CPlayerState::enPlayerStateSky:
		//�n�ʂɒ��n���Ă��邩�ǂ���
		return !m_groundCollision.IsHit();
	}
}