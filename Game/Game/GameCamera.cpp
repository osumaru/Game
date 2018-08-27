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
	camera.SetPosition({ 0.0f, 5.0f, 10.0f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	camera.Update();
	Add(this, 0);
	m_cameraVec = camera.GetPosition();
}

void GameCamera::Update()
{
	float rStick_x = GetPad().GetRightStickX() * 10 * GetGameTime().GetDeltaFrameTime();
	float rStick_y = GetPad().GetRightStickY() * 10 * GetGameTime().GetDeltaFrameTime();

	if (fabsf(rStick_x) > 0.0f) {
		//Y軸周りの回転
		Matrix matrix;
		matrix.MakeRotationY(0.01f * rStick_x);
		matrix.Mul(m_cameraVec);
	}
	if (fabsf(rStick_y) > 0.0f) {
		//X軸周りの回転
		Vector3 rotAxis;
		rotAxis.Cross(Vector3::Up, m_cameraVec);
		rotAxis.Normalize();
		Matrix matrix;
		matrix.MakeRotationAxis(rotAxis, 0.01f * rStick_y);
		//1フレーム前のカメラベクトル
		Vector3 cameraVecOld = m_cameraVec;

		matrix.Mul(m_cameraVec);
		Vector3 cameraDir = m_cameraVec;
		cameraDir.Normalize();

		if (cameraDir.y < -0.9f) {
			m_cameraVec = cameraVecOld;
		}
		else if (cameraDir.y > 0.9f) {
			m_cameraVec = cameraVecOld;
		}
	}

	Vector3 position = GetPlayer().GetPosition();
	camera.SetTarget(position);

	position += m_cameraVec;
	camera.SetPosition(position);
	camera.Update();
}