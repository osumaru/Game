#include "stdafx.h"
#include "GameCamera.h"
#include "Player\Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"

void CGameCamera::Init()
{
	camera.Init();
	camera.SetFar(300.0f);
	camera.SetNear(1.0f);
	camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	camera.SetAngle(CMath::DegToRad(60.0f));
	camera.SetPosition({ 0.0f, 1.8f, 3.2f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	m_normalCamera.Start(camera.GetPosition(), camera.GetTarget());
	m_arrowCamera.Start(camera.GetPosition(), camera.GetTarget());
	Add(this, 0);
	m_cameraVec = camera.GetPosition();
	PhysicsWorld().SetCamera(&camera);
	m_springCamera.Init(camera.GetTarget(), camera.GetPosition(), 5000.0f);
	Engine().GetDeferred().SetCamera(&camera);
}

void CGameCamera::Update()
{
	if (GetPlayer == nullptr) { return; }
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

	//m_cameraVec = camera.GetPosition() - camera.GetTarget();

	//if (fabsf(rStick_x) > 0.0f) {
	//	//Y������̉�]
	//	CMatrix matrix;
	//	matrix.MakeRotationY(rStick_x);
	//	matrix.Mul(m_cameraVec);
	//}
	//if (fabsf(rStick_y) > 0.0f) {
	//	//X������̉�]
	//	CVector3 rotAxis;
	//	rotAxis.Cross(CVector3::Up, m_cameraVec);
	//	rotAxis.Normalize();
	//	CMatrix matrix;
	//	matrix.MakeRotationAxis(rotAxis, rStick_y);
	//	//1�t���[���O�̃J�����x�N�g��
	//	CVector3 cameraVecOld = m_cameraVec;

	//	matrix.Mul(m_cameraVec);
	//	CVector3 cameraDir = m_cameraVec;
	//	cameraDir.Normalize();

	//	if (cameraDir.y < -0.5f)
	//	{
	//		m_cameraVec = cameraVecOld;
	//	}
	//	else if (cameraDir.y > 0.7f) 
	//	{
	//		m_cameraVec = cameraVecOld;
	//	}
	//}

	////�v���C���[�̌��ɒǏ]����J����
	//{
	//	CVector3 position, toCameraXZ;
	//	position = GetPlayer().GetPosition();
	//	toCameraXZ = m_cameraVec;
	//	float height = toCameraXZ.y;
	//	toCameraXZ.y = 0.0f;
	//	float toCameraLen = toCameraXZ.Length();
	//	toCameraXZ.Normalize();
	//	//�����_�̐ݒ�
	//	CVector3 target = GetPlayer().GetPosition();
	//	target.y += 1.5f;
	//	//�|���g�p���Ă���Ƃ��̃J����
	//	if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerArrowAttack||
	//		GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerArrowShoot)
	//	{
	//		CMatrix	mat = GetPlayer().GetPlayerSkin().GetWorldMatrix();
	//		CVector3 playerFlont = { -mat.m[0][0],-mat.m[0][1],-mat.m[0][2] };
	//		playerFlont.Normalize();
	//		target += playerFlont * 0.5f;
	//		camera.SetTarget(target);
	//		CVector3	toNewCameraPos = camera.GetPosition() - target;
	//		toNewCameraPos.Normalize();
	//		m_cameraVec.Normalize();
	//		position = target;
	//		position.Add(m_cameraVec);
	//		camera.SetPosition(position);
	//		
	//	}
	//	//�ʏ펞�̃J����
	//	else
	//	{

	//		CVector3	toNewCameraPos = camera.GetPosition() - target;
	//		toNewCameraPos.y = 0.0f;
	//		toNewCameraPos.Normalize();
	//		float weight = 0.3f;  //���̃E�F�C�g�̒l��0.0�`1.0�̒l���Ƃ�B1.0�ɋ߂Â��قǒǔ��������Ȃ�B
	//		toNewCameraPos = toNewCameraPos * weight + toCameraXZ * (1.0f - weight);
	//		toNewCameraPos.Normalize();
	//		toNewCameraPos *= toCameraLen;
	//		toNewCameraPos.y = height;              //������߂��B
	//		CVector3 pos = target + toNewCameraPos;  //����ŐV�������_������B
	//		camera.SetPosition(pos);
	//		camera.SetTarget(target);
	//		
	//	}
	//	
	//}
	camera.Update();
}