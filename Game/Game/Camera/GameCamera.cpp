#include "stdafx.h"
#include "GameCamera.h"
#include "../Player/Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"
#include "../Enemy/IEnemy.h"
#include "../Enemy/EnemyGroup.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"

CGameCamera *CGameCamera::m_gameCamera = NULL;

void CGameCamera::Init()
{
	//�J�����̏�����
	m_camera.Init();
	m_camera.SetFar(300.0f);
	m_camera.SetNear(1.0f);
	m_camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	m_camera.SetAngle(CMath::DegToRad(60.0f));
	m_camera.SetPosition({ 0.0f, 0.0f, 3.5f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetUp({ 0.0f, 1.0f, 0.0f });
	m_camera.Update();
	//Add(this, 0);
	//�����_����J�����ւ̃x�N�g�������߂�
	m_cameraVec = m_camera.GetPosition() - m_camera.GetTarget();
	//�������[���h�ɃJ������ݒ�
	PhysicsWorld().SetCamera(&m_camera);
	//�G���W���ɃJ������ݒ�
	Engine().GetDeferred().SetCamera(&m_camera);
	Engine().GetEffectEngine().SetCamera(&m_camera);
	Sky().Init(&m_camera);
	//�o�l�J�����̏�����
	m_springCamera.Init(m_camera.GetTarget(), m_camera.GetPosition(), 1000.0f);
	m_springCamera.SetDampingRate(0.7f);
	m_springCamera.SetPosition(m_camera.GetPosition());
	m_springCamera.SetTarget(m_camera.GetTarget());
	//�h��J�����̏�����
	m_shakeCamera.Init(CVector3::Zero, CVector3::Zero, {1.0f, 1.0f, 0.0f}, 0.7f);
}

void CGameCamera::CameraSetPlayer()
{
	m_pPlayerBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine2");
}

void CGameCamera::Update()
{
	if (&GetPlayer() == nullptr) { return; }
	if(GetPlayer().IsActive() == false) { return; }

	//��]������
	Rotation();
	//�����_��ݒ肷��
	CVector3 target;
	target.x = m_pPlayerBoneMat->m[3][0];
	target.y = m_pPlayerBoneMat->m[3][1];
	target.z = m_pPlayerBoneMat->m[3][2];
	//���W��ݒ肷��
	CVector3 position = target + m_cameraVec;

	//�E�X�e�B�b�N�������݂Ń��b�N�I��
	if (Pad().IsTriggerButton(enButtonRStickPush))
	{
		//�G�l�~�[�����b�N�I������
		RockOnEnemy();
	}
	//���b�N�I����
	if (m_isRockOn)
	{
		//���b�N�I�����Ă���G�l�~�[�����S������
		if (m_rockOnEnemy->GetStatus().hp <= 0)
		{
			//���b�N�I�����O��
			m_isRockOn = false;
		}
		else 
		{
			//�J�����̒����_��ݒ�
			target = m_rockOnEnemy->GetPosition();
			//�J�����̍��W�����߂�
			CVector3 playerPos = GetPlayer().GetPosition();
			CVector3 targetPos = m_camera.GetTarget();
			CVector3 cameraPos = playerPos - targetPos;
			cameraPos.Normalize();
			cameraPos *= 2.0f;
			cameraPos += playerPos;
			cameraPos.y += 2.5f;
			//�J�����̍��W��ݒ�
			position = cameraPos;
		}
	}

	//�o�l�J�������X�V����
	m_springCamera.SetTarTarget(target);
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	m_camera.SetPosition(m_springCamera.GetPosition());
	m_camera.SetTarget(m_springCamera.GetTarget());
	//�h��J�����̍��W�ƒ����_��ݒ肵�čX�V����
	m_shakeCamera.SetPosition(m_camera.GetPosition());
	m_shakeCamera.SetTarget(m_camera.GetTarget());
	m_shakeCamera.Update();
	//�J�����̍��W�ƒ����_��ݒ肵�čX�V����
	m_camera.SetPosition(m_shakeCamera.GetShakePosition());
	m_camera.SetTarget(m_shakeCamera.GetShakeTarget());
	m_camera.Update();
}

void CGameCamera::Rotation()
{
	//�X�e�B�b�N�̓��͗ʂ��擾
	float rStick_x = Pad().GetRightStickX();
	float rStick_y = Pad().GetRightStickY();
	//�����_����J�����܂ł̃x�N�g�������߂�
	m_cameraVec = m_camera.GetPosition() - m_camera.GetTarget();
	if (fabsf(rStick_x) > 0.0f) 
	{
		//Y������̉�]
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(m_cameraVec);
	}
	if (fabsf(rStick_y) > 0.0f)
	{
		//X������̉�]
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_cameraVec);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		//1�t���[���O�̃J�����x�N�g��
		CVector3 cameraVecOld = m_cameraVec;
		//�J�������璍���_�܂ł̃x�N�g������]������
		matrix.Mul(m_cameraVec);
		CVector3 cameraDir = m_cameraVec;
		cameraDir.Normalize();
		if (cameraDir.y < -0.8f)
		{
			//�J��������������������
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f)
		{
			//�J�������������������
			m_cameraVec = cameraVecOld;
		}
	}
	m_cameraVec.Normalize();
	m_cameraVec.Scale(3.5f);
}

void CGameCamera::RockOnEnemy()
{
	if (m_isRockOn)
	{
		//���b�N�I�����Ă邩��O��
		m_isRockOn = false;
		return;
	}

	float minLength = FLT_MAX;
	//�G�l�~�[�O���[�v�̃��X�g���擾
	std::list<CEnemyGroup*> enemyGroupList = GetSceneManager().GetMap()->GetEnemyGroupList();
	for (CEnemyGroup* enemyGroup : enemyGroupList)
	{
		CVector3 enemyGroupPos = enemyGroup->GetPosition();
		CVector3 playerPos = GetPlayer().GetPosition();
		//�G�l�~�[�O���[�v�ƃv���C���[�̋��������߂�
		CVector3 distance = playerPos - enemyGroupPos;
		float length = distance.Length();
		if (length < 30.0f)
		{
			//�G�l�~�[�O���[�v�̒��̃G�l�~�[���X�g���擾
			std::list<IEnemy*> enemyList = enemyGroup->GetGroupList();
			for (IEnemy* enemy : enemyList)
			{
				CVector3 enemyPos = enemy->GetPosition();
				//�G�l�~�[�ƃv���C���[�̋��������߂�
				distance = playerPos - enemyPos;
				length = distance.Length();
				if (length < minLength)
				{
					//���b�N�I������
					m_isRockOn = true;
					minLength = length;
					m_rockOnEnemy = enemy;
				}
			}
		}
	}
}