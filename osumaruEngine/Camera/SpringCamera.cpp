#include "engineStdafx.h"
#include "SpringCamera.h"
#include "../Timer/GameTime.h"
CSpringCamera::CSpringCamera() :
	m_camera(),
	m_target(0.0f, 0.0f, 0.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_targetMoveSpeed(0.0f, 0.0f, 0.0f),
	m_positionMoveSpeed(0.0f, 0.0f, 0.0f),
	m_maxMoveSpeed(0.0f),
	m_targetDampingRate(1.0f),
	m_dampingRate(1.0f),
	m_dampingRateVel(0.0f),
	m_dampingK(30.0f)
{

}

CSpringCamera::~CSpringCamera()
{

}

void CSpringCamera::Init(const CVector3& target, const CVector3& position, float maxMoveSpeed)
{
	m_camera.SetTarget(target);

	m_camera.SetPosition(position);
	m_target = target;
	m_position = position;
	m_targetMoveSpeed = { 0.0f, 0.0f, 0.0f };
	m_positionMoveSpeed = { 0.0f, 0.0f, 0.0f };
	m_maxMoveSpeed = maxMoveSpeed;
}

float CSpringCamera::CalcSpringScalar(float positionNow, float positionTarget, float& moveSpeed)
{
	float deltaTime = GameTime().GetDeltaFrameTime();
	float dampingRate = 0.2f;
	float distance = positionTarget - positionNow;
	if (fabsf(distance) < FLT_EPSILON)
	{
		moveSpeed = 0.0f;
		return positionTarget;
	}
	float originalDir = distance;
	originalDir /= fabsf(distance);
	float springAccel = distance;

	float t = m_dampingK / (2.0f * dampingRate);
	float springK = t * t;
	springAccel *= springK;
	//加速度を決定。
	float vt = moveSpeed;
	vt *= m_dampingK;
	springAccel -= vt;
	springAccel *= deltaTime;
	moveSpeed += springAccel;

	float newPos = positionNow;
	float addPos = moveSpeed;
	addPos *= deltaTime;
	newPos += addPos;
	vt = positionTarget - newPos;
	if (fabsf(vt) < FLT_EPSILON)
	{
		//目標座標まで移動完了した
		newPos = positionTarget;
		moveSpeed = 0.0f;
	}
	else
	{
		if (vt * originalDir < 0.0f)
		{
			//目標座標を超えた。
			newPos = positionTarget;
			moveSpeed = 0.0f;
		}
	}
	return newPos;
}

CVector3 CSpringCamera::CalcSpringVector(const CVector3& positionNow, const CVector3& positionTarget, CVector3& moveSpeed, float maxMoveSpeed, float dampingRate)
{
	float deltaTime = GameTime().GetDeltaFrameTime();
	//現在の位置と目標の位置との差分を求める。
	CVector3 distance;
	distance = positionTarget - positionNow;
	CVector3 originalDir = distance;
	originalDir.Normalize();
	CVector3 springAccel;
	springAccel = distance;
	
	float t = m_dampingK / (2.0f * dampingRate);
	float springK = t * t;
	springAccel *= springK;
	//加速度を決定。
	CVector3 vt = moveSpeed;
	vt *= m_dampingK;
	springAccel -= vt;

	springAccel *= deltaTime;
	moveSpeed += springAccel;
	if (moveSpeed.LengthSq() > maxMoveSpeed * maxMoveSpeed)
	{
		//最高速度より早くなってしまった
		moveSpeed.Normalize();
		moveSpeed *= maxMoveSpeed;
	}
	CVector3 newPos = positionNow;
	CVector3 addPos = moveSpeed;
	addPos *= deltaTime;
	newPos += addPos;
	vt = positionTarget - newPos;
	vt.Normalize();
	if (vt.Dot(originalDir) < 0.0f)
	{
		//目標座標を超えた
		newPos = positionTarget;
		moveSpeed = { 0.0f, 0.0f, 0.0f };
	}
	return newPos;

}

void CSpringCamera::UpdateSpringCamera()
{
	m_dampingRate = CalcSpringScalar(m_dampingRate, m_targetDampingRate, m_dampingRateVel);
	CVector3 target = CalcSpringVector(m_camera.GetTarget(), m_target, m_targetMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	CVector3 position = CalcSpringVector(m_camera.GetPosition(), m_position, m_positionMoveSpeed, m_maxMoveSpeed, m_dampingRate);
	m_camera.SetTarget(target);
	m_camera.SetPosition(position);
}

void CSpringCamera::Update()
{
	UpdateSpringCamera();
	UpdateCamera();
}