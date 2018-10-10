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

	//カメラを取得
	const CCamera& GetCamera()
	{
		return camera;
	}

	//ビュー行列を取得
	CMatrix GetViewMatrix()
	{
		return camera.GetViewMatrix();
		//return m_springCamera.GetSpringViewMatrix();
	}

	//プロジェクション行列を取得
	CMatrix GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
		//return m_springCamera.GetProjectionMatrix();
	}

	//バネカメラのプロジェクション行列の取得
	const CMatrix GetSpringProjectionMatrix()
	{
		return m_springCamera.GetProjectionMatrix();
	}
	//バネカメラのビュー行列の取得
	const CMatrix GetSpringViewMatrix()
	{
		return m_springCamera.GetSpringViewMatrix();
	}

private:
	CCamera camera;			//カメラ
	CVector3 m_cameraVec;	//注視点からカメラへのベクトル
	CSpringCamera	m_springCamera;
	CVector3 m_arrowCamera;	//弓を構えている時のカメラの位置

};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}