#include "ShakeCamera.h"

void CShakeCamera::Init(const CVector3 & position, const CVector3 & target, const CVector3 & shakeDirection, float shakePower)
{
	m_position = position;
	m_target = target;
	m_shakeDirection = shakeDirection;
	m_shakePower = shakePower;
}

void CShakeCamera::Update()
{
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

}
