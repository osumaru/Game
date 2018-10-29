/*
*	ゲームカメラクラス
*/

#pragma once
#include "NormalGameCamera.h"
#include "ArrowGameCamera.h"

class CGameCamera : IGameObject
{
public:

	enum EnCameraState 
	{
		enNormal,
		enArrow,
		enFree,
		enNum,
	};
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

	//バネカメラの取得
	const CSpringCamera& GetSpringCamera()
	{
		return m_springCamera;
	}

	//カメラのポジションを設定
	//第一引数　カメラの座標　第二引数　ターゲットの座標
	void SetCameraPosition(const CVector3 pos,const CVector3 tag)
	{

		m_springCamera.SetTarPosition(pos);
		m_springCamera.SetTarTarget(tag);
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

	////バネカメラのプロジェクション行列の取得
	//const CMatrix GetSpringProjectionMatrix()
	//{
	//	return m_springCamera.GetProjectionMatrix();
	//}
	////バネカメラのビュー行列の取得
	//const CMatrix GetSpringViewMatrix()
	//{
	//	return m_springCamera.GetSpringViewMatrix();
	//}
	void SetCmareaState(EnCameraState cameraState)
	{
		m_cameraState = cameraState;
	}

private:
	CCamera camera;			//カメラ
	EnCameraState	m_cameraState = EnCameraState::enNormal;
	CNormalGameCamera	m_normalCamera;
	CArrowGameCamera	m_arrowCamera;
	CVector3 m_cameraVec;	//注視点からカメラへのベクトル
	CSpringCamera	m_springCamera;

};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}