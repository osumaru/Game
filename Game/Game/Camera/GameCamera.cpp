#include "stdafx.h"
#include "GameCamera.h"
#include "../Player/Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"
#include "../Enemy/IEnemy.h"
#include "../Enemy/EnemyGroup.h"
#include "../Enemy/Maw.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"

CGameCamera *CGameCamera::m_gameCamera = NULL;

void CGameCamera::Init()
{
	//�J�����̏�����
	m_camera.Init();
	m_camera.SetFar(200.0f);
	m_camera.SetNear(1.0f);
	m_camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	m_camera.SetAngle(CMath::DegToRad(60.0f));
	m_camera.SetPosition({ 0.0f, 1.0f, -3.5f });
	m_camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	m_camera.SetUp({ 0.0f, 1.0f, 0.0f });
	m_camera.Update();
	//Add(this, 0);
	//�G���W���ɃJ������ݒ�
	Engine().SetCamera(&m_camera);
	//�o�l�J�����̏�����
	m_springCamera.Init(m_camera.GetTarget(), m_camera.GetPosition(), 1000.0f);
	m_springCamera.SetPosition(m_camera.GetPosition());
	m_springCamera.SetTarget(m_camera.GetTarget());
	//�h��J�����̏�����
	m_shakeCamera.Init(CVector3::Zero, CVector3::Zero, {1.0f, 1.0f, 0.0f}, 0.7f);
	//�J�����̓����蔻���������
	m_cameraCollisionSolver.Init(0.2f);
}

void CGameCamera::CameraSetPlayer()
{
	//�����_��ݒ肷��
	CVector3 target = GetPlayer().GetCharacterController().GetPosition();
	target.y += TARGET_OFFSET_Y;
	m_springCamera.SetTarTarget(target);
	//���W��ݒ肷��
	CVector3 toCameraPos = { 0.0f, 0.0f, -3.5f };
	CVector3 position = target + toCameraPos;
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	//�����_����J�����܂ł̋��������߂�
	m_cameraLength = toCameraPos.Length();
}

void CGameCamera::Update()
{
	if (&GetPlayer() == nullptr) { return; }
	if(GetPlayer().IsActive() == false) { return; }

	CVector3 target = m_springCamera.GetTarTarget();
	CVector3 position = m_springCamera.GetTarPosition();

	//�E�X�e�B�b�N�������݂Ń��b�N�I��
	if (Pad().IsTriggerButton(enButtonRStickPush))
	{
		if (!m_isLockOn) 
		{
			//���b�N�I������Ώۂ�T��
			SearchTarget();
		}
		else 
		{
			//���b�N�I������������
			LockOnCancel(target, position);
		}
	}

	//���b�N�I����
	if (m_isLockOn)
	{
		//�G�l�~�[�����b�N�I������
		LockOn(target, position);
	}
	else
	{
		//��]������
		Rotation(target, position);
	}

	////�J�����̍��W�ƒ����_���߂���΍��W�ƒ����_���X�V���Ȃ�
	//float currentHeight = m_camera.GetPosition().y - target.y;
	//if (m_cameraVec.y > 0.0f && currentHeight > 0.0f && fabsf(currentHeight) < m_height)
	//{
	//	target.y = m_camera.GetTarget().y;
	//	position.y = target.y + m_cameraVec.y;
	//}

	//�J�����̓����蔻��
	CVector3 newPos;
	if (m_cameraCollisionSolver.Execute(newPos, position, target))
	{
		position = newPos;
	}

	//�o�l�J�������X�V����
	m_springCamera.SetTarTarget(target);
	m_springCamera.SetTarPosition(position);
	m_springCamera.Update();
	m_camera.SetTarget(m_springCamera.GetTarget());
	m_camera.SetPosition(m_springCamera.GetPosition());
	//�h��J�����̍��W�ƒ����_��ݒ肵�čX�V����
	m_shakeCamera.SetTarget(m_camera.GetTarget());
	m_shakeCamera.SetPosition(m_camera.GetPosition());
	m_shakeCamera.Update();
	//�J�����̍��W�ƒ����_��ݒ肵�čX�V����
	m_camera.SetTarget(m_shakeCamera.GetShakeTarget());
	m_camera.SetPosition(m_shakeCamera.GetShakePosition());
	m_camera.Update();
}

void CGameCamera::Rotation(CVector3& target, CVector3& position)
{
	//�X�e�B�b�N�̓��͗ʂ��擾
	float rStick_x = Pad().GetRightStickX();
	float rStick_y = Pad().GetRightStickY();
	//�����_����J�����܂ł̃x�N�g�������߂�
	CVector3 toCameraPos = position - target;
	toCameraPos.Normalize();
	const float	CAMERA_SPEED = 2.0f;
	if (fabsf(rStick_x) > 0.0f) 
	{
		//Y������̉�]
		CMatrix matrix;
		matrix.MakeRotationY(rStick_x * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		matrix.Mul(toCameraPos);
	}
	if (fabsf(rStick_y) > 0.0f)
	{
		//X������̉�]
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, toCameraPos);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, rStick_y * CAMERA_SPEED * GameTime().GetDeltaFrameTime());
		//1�t���[���O�̃J�����x�N�g��
		CVector3 cameraVecOld = toCameraPos;
		//�J�������璍���_�܂ł̃x�N�g������]������
		matrix.Mul(toCameraPos);
		CVector3 cameraDir = toCameraPos;
		cameraDir.Normalize();
		if (cameraDir.y < -0.8f)
		{
			//�J��������������������
			toCameraPos = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f)
		{
			//�J�������������������
			toCameraPos = cameraVecOld;
		}
	}

	//�����_��ݒ肷��
	target = GetPlayer().GetCharacterController().GetPosition();
	target.y += TARGET_OFFSET_Y;
	//���W��ݒ肷��
	position = target + toCameraPos * m_cameraLength;
}

void CGameCamera::SearchTarget()
{
	if (&GetMaw().GetInstance() != nullptr && m_lockOnState != enLockOn_Boss)
	{
		m_lockOnState = enLockOn_Boss;
		m_isLockOn = true;
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
		//���b�N�I���ł��鋗����ݒ�
		const float	LOCKON_LENGTH = 30.0f;	
		if (length < LOCKON_LENGTH)
		{
			//�G�l�~�[�O���[�v�̒��̃G�l�~�[���X�g���擾
			std::list<IEnemy*> enemyList = enemyGroup->GetGroupList();
			for (IEnemy* enemy : enemyList)
			{
				if (enemy->GetIsDead())
				{
					continue;
				}
				CVector3 enemyPos = enemy->GetPosition();
				//�G�l�~�[�ƃv���C���[�̋��������߂�
				distance = playerPos - enemyPos;
				length = distance.Length();
				if (length < minLength)
				{
					//��ԋ߂��G�l�~�[�����b�N�I������
					m_isLockOn = true;
					minLength = length;
					m_rockOnEnemy = enemy;
					m_lockOnState = enLockOn_Enemy;
				}
			}
		}
	}
}

void CGameCamera::LockOn(CVector3& target, CVector3& position)
{
	CVector3 targetPosition;
	if (m_lockOnState == enLockOn_Boss)
	{
		if (GetMaw().GetSmawStatus().Hp <= 0)
		{
			//���b�N�I�����O��
			LockOnCancel(target, position);
			return;
		}
		targetPosition = GetMaw().GetPosition();
		targetPosition.y += 3.0f;
	}
	else
	{
		//���b�N�I�����Ă���G�l�~�[�����S������
		if (m_rockOnEnemy->GetIsDead())
		{
			//���b�N�I�����O��
			LockOnCancel(target, position);
			return;
		}
		targetPosition = m_rockOnEnemy->GetPosition();
		targetPosition.y += 0.5f;
	}

	//�^�[�Q�b�g�̍��W�𒍎��_�ɐݒ�
	target = targetPosition;
	//�^�[�Q�[�g����J�����ւ̃x�N�g�������߂�
	CVector3 playerPos = GetPlayer().GetCharacterController().GetPosition();
	CVector3 cameraVec = playerPos - target;
	cameraVec.y = 0.0f;
	//���������߂�
	float length = cameraVec.Length();
	//���_�̓v���C���[�����苗�����ɂ���
	cameraVec.Normalize();
	cameraVec *= m_cameraLength;
	cameraVec += playerPos;
	cameraVec.y = playerPos.y + LOCKON_OFFSET_Y;
	//�^�[�Q�b�g�Ƌ߂�����J�����̍����ɕ␳��������
	if (m_lockOnState == enLockOn_Enemy && length < LOCKON_OFFSET_Y)
	{
		//�����͋������߂��قǍ���
		cameraVec.y += LOCKON_OFFSET_Y - length;
	}
	//���_�ɐݒ�
	position = cameraVec;
}

void CGameCamera::LockOnCancel(CVector3& target, CVector3& position)
{
	//���b�N�I������߂�
	m_isLockOn = false;
	m_lockOnState = enLockOn_None;
	//���݂̒����_����J�����ւ̃x�N�g�������߂�
	CVector3 toCameraPos = position - target;
	toCameraPos.Normalize();
	toCameraPos *= m_cameraLength;
	//�����_�����߂�
	target = GetPlayer().GetCharacterController().GetPosition();
	target.y += TARGET_OFFSET_Y;
	//���W�����߂�
	position = target + toCameraPos;
}
