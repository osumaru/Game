#include "TwinSword.h"
#include "../Player.h"

void CTwinSword::Init()
{
	m_position = { 0.0f, 0.0f, -10.0f };
	m_rotation = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation.Multiply(multi);

	m_attackRotation = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackRotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackRotation.Multiply(multi);
	m_attackPosition = { -10.0f, 0.0f, 0.0f };

	m_skinModel.Load(L"Assets/modelData/TwinSword.cmo", NULL);
}