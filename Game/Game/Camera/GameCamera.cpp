#include "stdafx.h"
#include "GameCamera.h"
#include "../Player/Player.h"
#include "../Player/PlayerSate/PlayerStateMachine.h"

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
	//m_springCamera.Update();
	//m_camera.SetPosition(m_springCamera.GetPosition());
	//m_camera.SetTarget(m_springCamera.GetTarget());
	m_camera.Update();
}