/*
*	ゲームカメラクラス
*/

#pragma once

class CGameCamera : IGameObject
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//ゲームカメラのインスタンスを取得
	static CGameCamera& GetInstance()
	{
		static CGameCamera gamecamera;
		return gamecamera;
	}

	//ビュー行列を取得
	CMatrix GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}

	//プロジェクション行列を取得
	CMatrix GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}



private:
	CCamera camera;			//カメラ
	CVector3 m_cameraVec;	//注視点からカメラへのベクトル
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}