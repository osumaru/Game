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
	camera.SetPosition({ 0.0f, 1.5f, 5.2f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	m_normalCamera.Start(camera.GetPosition(), camera.GetTarget());
	m_arrowCamera.Start(camera.GetPosition(), camera.GetTarget());
	Add(this, 0);
	m_cameraVec = camera.GetPosition();
	//PhysicsWorld().SetCamera(&camera);
	m_springCamera.Init(camera.GetTarget(), camera.GetPosition(), 10000.0f);
	//PhysicsWorld().SetCamera(m_springCamera.GetCamera());
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
	m_springCamera.Update();
}