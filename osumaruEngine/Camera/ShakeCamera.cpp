#include "ShakeCamera.h"

void CShakeCamera::Init(const CVector3 & position, const CVector3 & target, const CVector3 & shakeDirection, float damping)
{
	m_position = position;
	m_target = target;
	m_shakePosition = position;
	m_shakeTarget = target;
	m_shakeDirection = shakeDirection;
	m_damping = damping;
}

void CShakeCamera::Update()
{
	m_shakePosition = m_position;
	m_shakeTarget = m_target;
	if (fabs(m_shakePower) <= 0.0f)
	{
		return;
	}
	CVector3 shakeDir = m_shakeDirection;
	shakeDir.Normalize();
	CVector3 front = m_target - m_position;
	CVector3 right;
	right.Cross(CVector3::Up, front);
	CVector3 up;
	up.Cross(right, front);
	up.Normalize();
	front.Normalize();
	right.Normalize();
	CVector3 shakeVector = right * shakeDir.x;
	shakeVector += up * shakeDir.y;
	shakeVector += front * shakeDir.z;
	shakeVector.Normalize();
	shakeVector *= m_shakePower;
	m_shakePower *= -m_damping;
	m_shakePosition += shakeVector;
	m_shakeTarget += shakeVector;
	if (fabs(m_shakePower) < 0.00001f)
	{
		m_shakePower = 0.0f;
	}
}
