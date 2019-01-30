/*
*	ゲームカメラクラス
*/

#pragma once

#include "CameraCollisionSolver.h"

class IEnemy;

class CGameCamera : public IGameObject
{
public:
	//初期化
	void Init();
	
	//更新
	void Update();

	void PostAfterDraw()override;

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

	//弓装備中にズームしているかを取得
	bool GetIsArrowZoom()
	{
		return m_isArrowZoom;
	}

	//弓装備中にズームしているかを設定
	//isArrowZoom	弓装備中にズームしているか
	void SetIsArrowZoom(bool isArrowZoom)
	{
		m_isArrowZoom = isArrowZoom;
	}

private:
	//カメラへのベクトルを回転する
	void Rotation();

	//ロックオンする対象を探す
	void SearchTarget();

	//ロックオン対象を切り替える
	void ChangeTarget();

	//ロックオンする
	//target	ターゲットの座標
	void LockOn(CVector3& target);

	//ロックオンを解除する
	void LockOnCancel();

private:
	enum EnLockOnState
	{
		enLockOn_None,	//何もない
		enLockOn_Enemy,	//エネミー
		enLockOn_Boss	//ボス
	};
	CSprite					m_reticule;
	CSprite					m_lockOnSprite;				//ロックオンスプライト				
	static CGameCamera*		m_gameCamera;				//ゲームカメラ
	CCamera					m_camera;					//カメラ
	CSpringCamera			m_springCamera;				//バネカメラ
	CShakeCamera			m_shakeCamera;				//揺れカメラ
	CCameraCollisionSolver	m_cameraCollisionSolver;	//カメラの当たり判定
	EnLockOnState			m_lockOnState = enLockOn_None;	//何をロックオンしているか
	IEnemy*					m_lockOnEnemy = nullptr;	//ロックオンしているエネミー
	CVector3				m_toCameraPos;				//カメラへのベクトル
	float					m_cameraLength = 0.0f;		//注視点からカメラへの距離
	float					m_preRStick = 0.0f;			//1フレーム前のパッド入力量
	const float				LOCKON_OFFSET_Y = 2.5f;		//ロックオン時の高さ補正の限界値
	const float				TARGET_OFFSET_Y = 1.4f;		//カメラ通常時の高さ補正
	//float					m_height = 0.0f;			//カメラの座標と注視点の高さ
	int						m_lockOnEnemyNumber = 0;	//ロックオンしているエネミー番号
	bool					m_isLockOn = false;			//ロックオンしているか
	bool					m_isArrowZoom = false;		//弓装備中にズームしているか
};

static CGameCamera& GetGameCamera()
{
	return CGameCamera::GetInstance();
}