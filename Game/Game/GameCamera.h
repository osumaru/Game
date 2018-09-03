#pragma once

class CGameCamera : GameObject
{
public:

	void Init();

	void Update();

	static CGameCamera& GetInstance()
	{
		static CGameCamera gamecamera;
		return gamecamera;
	}

	Matrix GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}

	Matrix GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}



private:
	Camera camera;
	Vector3 m_cameraVec;
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}