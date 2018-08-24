#pragma once

class GameCamera : GameObject
{
public:

	void Init();

	void Update();

	static GameCamera& GetInstance()
	{
		static GameCamera gamecamera;
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
};

static GameCamera& GetGameCamera()
{
	return GameCamera::GetInstance();
}