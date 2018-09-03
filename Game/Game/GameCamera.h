#pragma once

class CGameCamera : IGameObject
{
public:

	void Init();

	void Update();

	static CGameCamera& GetInstance()
	{
		static CGameCamera gamecamera;
		return gamecamera;
	}

	CMatrix GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}

	CMatrix GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}



private:
	CCamera camera;
	CVector3 m_cameraVec;
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}