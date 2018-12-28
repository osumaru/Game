#pragma once

class CShakeCamera
{
public:
	/*
	初期化
	position		カメラの座標
	target			カメラの注視点
	shakeDirection	揺れ方向
	damping			減衰率
	*/
	void Init(const CVector3& position, const CVector3& target, const CVector3& shakeDirection, float damping);

	/*
	揺れスタート
	shakePower	揺れる力
	*/
	void ShakeStart(float shakePower)
	{
		m_shakePower = shakePower;
	}

	//座標を設定
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//注視点を設定
	void SetTarget(const CVector3& target)
	{
		m_target = target;
	}

	//注視点を取得
	const CVector3& GetTarget() const
	{
		return m_target;
	}

	//揺れた後のカメラの座標を取得
	const CVector3& GetShakePosition() const
	{
		return m_shakePosition;
	}

	//揺れた後の注視点を取得
	const CVector3& GetShakeTarget() const
	{
		return m_shakeTarget;
	}
	//更新
	void Update();

	//揺れの強さを設定
	void SetShakeDirection(const CVector3& shakeDirection)
	{
		m_shakeDirection = shakeDirection;
	}

	//遅延時間を設定
	void SetDelayTime(float delayTime)
	{
		m_delayTime = delayTime;
	}
	//遅延しているフレーム数を設定
	void SetDelayCount(int delayCount)
	{
		m_delayCount = delayCount;
	}

private:
	CVector3	m_position;			//カメラの座標
	CVector3	m_target;			//注視点の座標
	CVector3	m_shakeTarget;		//揺れた後の注視点
	CVector3	m_shakePosition;	//揺れた後のカメラの座標
	CVector3	m_shakeDirection;	//揺れ方向
	float		m_shakePower;		//揺れる力
	float		m_damping;			//揺れの減衰率
	float		m_delayTime = 0.0f;	//揺れまでの遅延時間
	int			m_delayCount = 0;	//揺れまでの遅延するフレーム数
};