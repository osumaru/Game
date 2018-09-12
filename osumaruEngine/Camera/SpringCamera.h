#pragma once
#include "Camera.h"
//バネカメラ

class CSpringCamera
{
public:
	//コンストラクタ
	CSpringCamera();

	//デストラクタ
	~CSpringCamera();

	/*
	初期化
	target			注視店
	position		座標
	maxMoveSpeed	最大速度
	*/
	void Init(const CVector3& target, const CVector3& position, float maxMoveSpeed);


	//目標となる注視点を設定。
	void SetTarTarget(const CVector3& target)
	{
		m_target = target;
	}

	//注視点を設定
	void SetTarget(const CVector3& target)
	{
		m_camera.SetTarget(target);
	}


	//目標となる視点を設定
	void SetTarPosition(const CVector3& position)
	{
		m_position = position;
	}

	//視点を設定
	void SetPosition(const CVector3& position)
	{
		m_camera.SetPosition(position);
	}

	//遠平面を取得
	void SetFar(float _far)
	{
		m_camera.SetFar(_far);
	}

	//注視点を取得
	const CVector3& GetTarget() const
	{
		return m_camera.GetTarget();
	}

	//視点を取得
	const CVector3& GetPosition() const
	{
		return m_camera.GetPosition();
	}

	//更新関数
	void Update();

	//カメラを取得
	const CCamera* GetCamera() const
	{
		return &m_camera;
	}

	/*
	バネの減衰率を設定
	dampingRate		減衰率、この値が大きいほどカメラが遅れてついてくる
	*/
	void SetDampingRate(float dampingRate)
	{
		m_targetDampingRate = dampingRate;
	}

	//目標となる注視点を取得
	const CVector3& GetTarTarget() const
	{
		return m_target;
	}

	//目標となる視点を取得
	const CVector3& GetTarPosition() const
	{
		return m_position;
	}

	//バネカメラ用のパラメータをクリア
	void ClearSpringParame()
	{
		m_target = { 0.0f, 0.0f, 0.0f };
		m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	/*
	バネカメラの更新
	バネカメラのみ更新したいときに使う
	*/
	void UpdateSpringCamera();

	/*
	カメラの更新
	カメラのみ更新したいときに使う
	*/
	void UpdateCamera()
	{
		m_camera.Update();
	}

	//プロジェクション行列を取得
	const CMatrix& GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}
	
	//ビュー行列を取得
	const CMatrix& GetSpringViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}

private:

	/*
	現在の座標から目標の座標までバネ計算をした結果を求める
	positionNow		現在の座標
	positionTarget	目標の座標
	moveSpeed		移動速度
	maxMoveSpeed	最大速度
	danpingRate		減衰率
	ret				計算後の座標
	*/
	CVector3 CalcSpringVector(const CVector3& positionNow, const CVector3& positionTarget, CVector3& moveSpeed, float maxMoveSpeed, float dampingRate);

	/*
	減衰率を求める
	positionNow		現在の減衰率
	positionTarget	目標の減衰率
	moveSpeed		加速度
	ret　			計算後の減衰率
	*/
	float CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed);

	

private:
	CCamera			m_camera;				//カメラ
	CVector3		m_target;				//注視点
	CVector3		m_position;				//座標
	CVector3		m_targetMoveSpeed;		//現在の注視点から目標の注視店までの移動速度
	CVector3		m_positionMoveSpeed;	//現在の座標から目標の座標までの移動速度
	float			m_maxMoveSpeed;			//バネカメラの最大速度
	float			m_targetDampingRate;	//目標の減衰率
	float			m_dampingRate;			//現在の減衰率
	float			m_dampingRateVel;		//減衰率の加速度
	const float		m_dampingK;				//減衰率の係数
};