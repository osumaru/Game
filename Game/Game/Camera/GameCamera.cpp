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
	camera.SetPosition({ 0.0f, 0.0f, 3.5f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	m_normalCamera.Start(camera.GetPosition(), camera.GetTarget());
	m_arrowCamera.Start(camera.GetPosition(), camera.GetTarget());
	Add(this, 0);
	m_cameraVec = camera.GetPosition();
	m_springCamera.Init(camera.GetTarget(), camera.GetPosition(), 10000.0f);
	PhysicsWorld().SetCamera(&camera);
	Engine().GetDeferred().SetCamera(&camera);
	Sky().Init(&camera);
	CVector3 cameraDir = camera.GetTarget() - camera.GetPosition();
	CVector3 cameraPos = GetPlayer().GetPosition() + cameraDir;
	m_springCamera.SetPosition(cameraPos);
	m_springCamera.SetTarget(GetPlayer().GetPosition());

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
	m_springCamera.Update();
	camera.SetPosition(m_springCamera.GetPosition());
	camera.SetTarget(m_springCamera.GetTarget());
	camera.Update();
}