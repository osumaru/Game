#include "stdafx.h"
#include "GameCamera.h"
#include "Player\Player.h"

void CGameCamera::Init()
{
	camera.Init();
	camera.SetFar(10000.0f);
	camera.SetNear(1.0f);
	camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	camera.SetAngle(CMath::DegToRad(60.0f));
	camera.SetPosition({ 0.0f, 1.5f, 1.5f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	Add(this, 0);
	m_cameraVec = camera.GetPosition();
	PhysicsWorld().SetCamera(&camera);

	m_springCamera.Init(camera.GetTarget(), camera.GetPosition(), 1.0f);
	
}

void CGameCamera::Update()
{
	float rStick_x = Pad().GetRightStickX() * 180 * GameTime().GetDeltaFrameTime();
	float rStick_y = Pad().GetRightStickY() * 180 * GameTime().GetDeltaFrameTime();

	if (fabsf(rStick_x) > 0.0f) {
		//Y������̉�]
		CMatrix matrix;
		matrix.MakeRotationY(0.01f * rStick_x);
		matrix.Mul(m_cameraVec);
	}
	if (fabsf(rStick_y) > 0.0f) {
		//X������̉�]
		CVector3 rotAxis;
		rotAxis.Cross(CVector3::Up, m_cameraVec);
		rotAxis.Normalize();
		CMatrix matrix;
		matrix.MakeRotationAxis(rotAxis, 0.01f * rStick_y);
		//1�t���[���O�̃J�����x�N�g��
		CVector3 cameraVecOld = m_cameraVec;

		matrix.Mul(m_cameraVec);
		CVector3 cameraDir = m_cameraVec;
		cameraDir.Normalize();

		if (cameraDir.y < -0.9f) {
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f) {
			m_cameraVec = cameraVecOld;
		}
	}

	CVector3 position = GetPlayer().GetPosition();//GetPlayerHead();
	float interporation = 2.0f;
	position.y += interporation;	
	camera.SetTarget(position);
	m_springCamera.SetTarTarget(position);

	//position.y -= interporation;
	position += m_cameraVec;
	camera.SetPosition(position);
	m_springCamera.SetTarPosition(position);

	m_springCamera.Update();
	camera.Update();
}