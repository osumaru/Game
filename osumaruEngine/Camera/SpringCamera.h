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
		m_target = {0.0f, 0.0f, 0.0f};
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
private:

	/*
	positionNow		今の座標
	positionTarget	目標座標
	moveSpeed		移動速度
	*/
	CVector3 CalcSpringVector(const CVector3& positionNow, const CVector3& positionTarget, CVector3& moveSpeed, float maxMoveSpeed, float dampingRate);

	float CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed);

private:
	CCamera		m_camera;
	CVector3 m_target;
	CVector3 m_position;
	CVector3 m_targetMoveSpeed;
	CVector3 m_positionMoveSpeed;
	float		m_maxMoveSpeed;
	float		m_targetDampingRate;
	float		m_dampingRate;
	float		m_dampingRateVel;
	const float m_dampingK;
};