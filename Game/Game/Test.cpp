#include "stdafx.h"
#include "Test.h"



void Test::Init()
{
	texture.Load(L"Assets/sprite/CLEAR.png");

	sprite.Init(&texture);
	view.MakeLookAt({ 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f }, {0.0f, 1.0f, 0.0f});
	proj.MakeProjectionMatrix(Math::DegToRad(60.0f), (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT, 1.0f, 500.0f);
	model.Load(L"Assets/modelData/Unitychan.cmo");
}

void Test::Update()
{
	static float angle = 0.0f;
	angle += 0.2f;
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisY, angle);
	model.Update({ 0.0f, 0.0f, 0.0f }, rot, { 1.0f, 1.0f, 1.0f });
}

void Test::Draw()
{
	model.Draw(view, proj);
	//sprite.Draw();
}