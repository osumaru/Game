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
	m_camera.Init();
	m_camera.SetFar(300.0f);
	m_camera.SetNear(1.0f);
	m_camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	m_camera.SetAngle(CMath::DegToRad(60.0f));
	m_camera.SetPosition({ 0.0f, 0.0f, 3.5f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetUp({ 0.0f, 1.0f, 0.0f });
	m_camera.Update();
	m_normalCamera.Start(m_camera.GetPosition(), m_camera.GetTarget());
	m_arrowCamera.Start(m_camera.GetPosition(), m_camera.GetTarget());
	//Add(this, 0);
	m_cameraVec = m_camera.GetPosition();
	m_springCamera.Init(m_camera.GetTarget(), m_camera.GetPosition(), 10000.0f);
	PhysicsWorld().SetCamera(&m_camera);
	Engine().GetDeferred().SetCamera(&m_camera);
	Engine().GetEffectEngine().SetCamera(&m_camera);
	Sky().Init(&m_camera);
	CVector3 cameraDir = m_camera.GetTarget() - m_camera.GetPosition();
	CVector3 cameraPos = CVector3::Zero;//GetPlayer().GetPosition() + cameraDir;
	m_springCamera.SetPosition(cameraPos);
	m_springCamera.SetTarget(CVector3::Zero/*GetPlayer().GetPosition()*/);
	m_shakeCamera.Init(CVector3::Zero, CVector3::Zero, {1.0f, 1.0f, 0.0f}, 0.7f);
}

void CGameCamera::CameraSetPlayer()
{
	CVector3 cameraDir = m_camera.GetTarget() - m_camera.GetPosition();
	CVector3 cameraPos = GetPlayer().GetPosition() + cameraDir;
	m_springCamera.SetTarget(GetPlayer().GetPosition());
}

void CGameCamera::Update()
{
	if (&GetPlayer() == nullptr) { return; }
	if(GetPlayer().IsActive() == false) { return; }
	switch (m_cameraState)
	{
	case EnCameraState::enNormal:
		m_normalCamera.Update();
		break;

	case EnCameraState::enArrow:
		m_arrowCamera.Update();
		break;
	case EnCameraState::enFree:

		break;

	default:

		break;
	}

	//if (Pad().IsTriggerButton(enButtonRStickPush))
	//{
	//	//�G�l�~�[�����b�N�I������
	//	RockOnEnemy();
	//}

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
			m_camera.SetTarget(m_rockOnEnemy->GetPosition());
			//�J�����̍��W�����߂�
			CVector3 playerPos = GetPlayer().GetPosition();
			CVector3 targetPos = m_camera.GetTarget();
			CVector3 cameraPos = playerPos - targetPos;
			cameraPos.Normalize();
			cameraPos *= 2.0f;
			cameraPos += playerPos;
			cameraPos.y += 2.5f;
			//�J�����̍��W��ݒ�
			m_camera.SetPosition(cameraPos);
		}
	}

	//m_springCamera.Update();
	//m_camera.SetPosition(m_springCamera.GetPosition());
	//m_camera.SetTarget(m_springCamera.GetTarget());
	m_shakeCamera.SetPosition(m_camera.GetPosition());
	m_shakeCamera.SetTarget(m_camera.GetTarget());
	m_shakeCamera.Update();
	m_camera.SetPosition(m_shakeCamera.GetShakePosition());
	m_camera.SetTarget(m_shakeCamera.GetShakeTarget());
	m_camera.Update();
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