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

CPlayer *CPlayer::m_player = NULL;

void CPlayer::OnInvokeAnimationEvent(//�A�j���[�V�����C�x���g���Ă΂�邲�ƂɌĂяo�����H
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{

	if (wcscmp(animClipName, L"Assets/modelData/PlayerDash60fpsEvent.tka") == 0)
	{//�C�x���g���ŏ�����ς���H
		const float footVolume = 1.0f;
		CSoundSource* footSound = New<CSoundSource>(0);
		footSound->Init("Assets/sound/Jump.wav");
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

	if (!wcscmp(animClipName, L"Assets/modelData/PlayerCombo4.tka") ||
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
	//�v���C���[�̃X�L�������f���̃��[�h
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");

	m_position = position;
	m_skinmodel.Update(m_position, CQuaternion::Identity, CVector3::One);
	m_characterController.Init(0.3f, 1.0f, m_position);
	m_characterController.SetGravity(-30.0f);
	//���C�g�̐ݒ�
	Light().SetAmbientLight({ 0.5f,0.5f,0.5f,1.0f });
	Light().SetDiffuseLight(0, { 1.0f,1.0f,1.0f,1.0f });
	Light().SetDiffuseLightDir(0, { 0.0f, -1.0f, 1.0f, 1.0f });

	//�A�j���[�V�����̏�����
	{
		wchar_t* animClip[enPlayerAnimationNum] = {
									{ L"Assets/modelData/PlayerStand.tka"},				//�ҋ@�A�j���[�V����	
									{ L"Assets/modelData/PlayerWalkStay.tka" },			//���s�A�j���[�V����
									{ L"Assets/modelData/PlayerDash60fpsEvent.tka" },		//����A�j���[�V����
									{ L"Assets/modelData/PlayerRunJump.tka" },			//����W�����v�A�j���[�V����
									{ L"Assets/modelData/PlayerJump2.tka" },				//�W�����v�A�j���[�V����
									{ L"Assets/modelData/PlayerCombo4.tka" },			//�U���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo5.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo6.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo4Combine.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerCombo5Combine.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerAttackCombine.tka" },		//�A���A�j���[�V����
									{ L"Assets/modelData/PlayerStun.tka" },			//�X�^���A�j���[�V����
									{ L"Assets/modelData/PlayerDamage.tka" },			//�_���[�W�A�j���[�V����
									{ L"Assets/modelData/PlayerRoll.tka" }	,		//����A�N�V����
									{ L"Assets/modelData/PlayerRollCombine.tka" }	,		//����A�N�V����
									{ L"Assets/modelData/PlayerDeath.tka" },			//���S�A�j���[�V����
									{ L"Assets/modelData/PlayerWireMove.tka" },				//���C���[�ړ��A�j���[�V����
									{ L"Assets/modelData/PlayerArrowAttack.tka" },		//�|�̍U���A�j���[�V����
									{ L"Assets/modelData/PlayerArrowAttackEvent.tka" },
									{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },	//�匕�̍U���A�j���[�V����
									{ L"Assets/modelData/PlayerTwinSwordAttack.tka" },	//�񓁗��̍U���A�j���[�V����
									{ L"Assets/modelData/PlayerLanding.tka" }
		};

		m_animation.Init(animClip, enPlayerAnimationNum);
		m_animation.SetLoopFlg(enPlayerAnimationStand, true);
		m_animation.SetLoopFlg(enPlayerAnimationWalk, true);
		m_animation.SetLoopFlg(enPlayerAnimationRun, true);
		m_animation.SetLoopFlg(enPlayerAnimationWireMove, true);

		//�A�j���[�V�����C�x���g���X�i�[�̓o�^�@�Ăяo�����֐��̓o�^�H
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
		{
			OnInvokeAnimationEvent(animClipname, eventName);
		});

	}


	//�v���C���[�̃X�e�[�^�X�̏�����
	{
		m_status.Strength = 10;						//�U����
		m_status.Defense = 3;						//�h���
		m_status.Health = 100;						//�̗�
		m_status.MaxHealth = m_status.Health;			//���x�����Ƃ̍ő�HP
		m_status.Level = 1;						//���x��
		m_status.OldExp = 15;						//�ЂƂO�̃��x���ɕK�v�Ȍo���l
		m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;		//���̃��x���A�b�v�ɕK�v�Ȍo���l
		m_status.ExperiencePoint = 0;					//�o���l
		m_status.AccumulationExp += m_status.OldExp;	//�ݐόo���l
		m_status.Gold = 4000;							//������
	}
	m_playerGetter.SetPlayer(this);
	m_PlayerStateMachine.SetPlayer(this, &m_playerGetter);
	m_PlayerStateMachine.Init();
	//Add(this, 1);
	m_skinmodel.SetIsShadowCaster(true);
	m_weaponManager.Init(this);
	m_wireAction.Init(this);
}



void CPlayer::Update()
{
	m_position = m_characterController.GetPosition();
	if (m_isDied)
	{
		return;
	}

	StatusCalculation();	//�X�e�[�^�X�̏���



	if (Pad().IsPressButton(enButtonX))
	{
		m_status.Health = 5;
	}

	CMatrix viewMat;
	CVector3 cameraPos = m_position;
	cameraPos.y += 50.0f;
	CVector3 shadowCameraUp = GetGameCamera().GetSpringCamera().GetTarget() - GetGameCamera().GetSpringCamera().GetPosition();
	shadowCameraUp.y = 0.0f;
	shadowCameraUp.Normalize();
	viewMat.MakeLookAt(cameraPos, m_position, CVector3::AxisX);
	CMatrix projMat;
	projMat.MakeOrthoProjectionMatrix(5, 5, 1.0f, 100.0f);
	Engine().GetShadowMap().SetViewMatrix(viewMat);
	Engine().GetShadowMap().SetProjectionMatrix(projMat);
	m_wireAction.Update();
	m_PlayerStateMachine.Update();
	Rotation();
	m_position = m_characterController.GetPosition();
	//�A�j���[�V�����̍X�V
	m_animation.Update(GameTime().GetDeltaFrameTime());
	//�X�L�����f���̍X�V
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_weaponManager.Update();
}

//�`�揈��
void CPlayer::Draw()
{
	//m_characterController.Draw();
	m_weaponManager.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CPlayer::AfterDraw()
{
	m_weaponManager.AfterDraw();
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

void CPlayer::Rotation()
{

	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
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
	m_rotation.SetRotation(CVector3::AxisY, rad);

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
		CVector3 moveSpeed = m_characterController.GetMoveSpeed();
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

void CPlayer::UseItem(int number)
{
	if (m_itemList.empty())
	{
		//�A�C�e�����Ȃ�
		return;
	}
	//�I�񂾃A�C�e�����g��
	std::list<IItem*>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < number; i++)
	{
		it++;
	}
	bool isUse = (*it)->Use();
	if (isUse) {
		//�g�����A�C�e�������X�g����폜����
		m_itemList.erase(it);
	}
}

void CPlayer::AddItemList(IItem * item)
{
	if (m_itemList.size() < CItemInventory::GetItemLimit())
	{
		//��������𒴂��Ă��Ȃ���΃A�C�e�����X�g�ɒǉ�
		m_itemList.push_back(item);
	}
}