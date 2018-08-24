#include "stdafx.h"
#include "GameCamera.h"
#include "Player\Player.h"

void GameCamera::Init()
{
	camera.Init();
	camera.SetFar(500.0f);
	camera.SetNear(1.0f);
	camera.SetAspect((float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT);
	camera.SetAngle(Math::DegToRad(60.0f));
	camera.SetPosition({ 0.0f, 0.0f, -200.0f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	Add(this, 0);
}

void GameCamera::Update()
{
	Vector3 position = GetPlayer().GetPosition();
	camera.SetTarget(position);
	position.z += 70.0f;
	position.y += 30.0f;
	camera.SetPosition(position);
	camera.Update();
}