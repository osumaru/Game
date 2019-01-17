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
		Engine().SetCamera(nullptr);
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

private:
	//回転
	//target	ターゲットの座標
	//position	カメラの座標
	void Rotation(CVector3& target, CVector3& position);

	//ロックオンする対象を探す
	void SearchTarget();

	//ロックオンする
	//target	ターゲットの座標
	//position	カメラの座標
	void LockOn(CVector3& target, CVector3& position);

	//ロックオンを解除する
	//target	ターゲットの座標
	//position	カメラの座標
	void LockOnCancel(CVector3& target, CVector3& position);

	static CGameCamera* m_gameCamera;			//ゲームカメラ
	CCamera				m_camera;				//カメラ
	CSpringCamera		m_springCamera;			//バネカメラ
	CShakeCamera		m_shakeCamera;			//揺れカメラ
	IEnemy*				m_rockOnEnemy;			//ロックオンしているエネミー
	float				m_cameraLength = 0.0f;	//注視点からカメラへの距離
	const float			LOCKON_OFFSET_Y = 2.5f;	//ロックオン時の高さ補正の限界値
	const float			TARGET_OFFSET_Y = 1.4f; //カメラ通常時の高さ補正
	float				m_height = 0.0f;		//カメラの座標と注視点の高さ
	bool				m_isLockOn = false;		//ロックオンしているか
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}