/*
*	ゲームカメラクラス
*/

#pragma once
#include "NormalGameCamera.h"
#include "ArrowGameCamera.h"

class IEnemy;

class CGameCamera : public IGameObject
{
public:
	//初期化
	void Init();
	
	//更新
	void Update();

	//回転
	void Rotation();
	
	//カメラ必要なプレイヤーの情報の初期化`
	void CameraSetPlayer();

	//ゲームカメラのインスタンスを取得
	static CGameCamera& GetInstance()
	{
		return *m_gameCamera;
	}

	//インスタンスの生成
	static void CGameCamera::Create()
	{
		if (!m_gameCamera)
		{
			m_gameCamera = New<CGameCamera>(PRIORITY_CAMERA);
		}
	}

	//インスタンスの消去
	static void CGameCamera::Destroy()
	{
		Delete(m_gameCamera);
		m_gameCamera = nullptr;
		PhysicsWorld().SetCamera(nullptr);
		Engine().GetDeferred().SetCamera(nullptr);
		Sky().SetCamera(nullptr);
	}

	//カメラを取得
	const CCamera& GetCamera()
	{
		return m_camera;
	}

	//バネカメラの取得
	const CSpringCamera& GetSpringCamera()
	{
		return m_springCamera;
	}

	//揺れカメラの取得
	CShakeCamera& GetShakeCamera()
	{
		return m_shakeCamera;
	}

	//ビュー行列を取得
	CMatrix GetViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}

	//プロジェクション行列を取得
	CMatrix GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}

	//エネミーをロックオンする
	void RockOnEnemy();

private:
	static CGameCamera* m_gameCamera;							//ゲームカメラ
	CCamera				m_camera;								//カメラ
	CVector3			m_cameraVec;							//注視点からカメラへのベクトル
	CSpringCamera		m_springCamera;							//バネカメラ
	CShakeCamera		m_shakeCamera;							//揺れカメラ
	IEnemy*				m_rockOnEnemy;							//ロックオンしているエネミー
	const CMatrix*		m_pPlayerBoneMat;						//注視点とするプレイヤーのボーンの行列
	const float			CAMERA_SPEED = 4.0f;					//カメラの回転速度
	bool				m_isRockOn = false;						//ロックオンしているか
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}