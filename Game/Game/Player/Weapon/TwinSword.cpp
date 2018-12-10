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

	m_maxAttackNum = 3;
	m_attackAnimation = new EnPlayerAnimation[m_maxAttackNum];
	m_combineAnimation = new EnPlayerAnimation[m_maxAttackNum];
	for (int i = 0; i < m_maxAttackNum; i++)
	{
		m_attackAnimation[i]=(EnPlayerAnimation)(enPlayerAnimationTwinAttack1+i);
		m_combineAnimation[i]= (EnPlayerAnimation)(enPlayerAnimationTwinAttackCombine1 + i);
	}

	m_stanAttack = new bool[m_maxAttackNum];
	m_stanAttack[0] = false;
	m_stanAttack[1] = false;
	m_stanAttack[2] = false;
}

SWeaponEnemyAttackInfo CTwinSword::EnemyAttackPositionDecide()
{
	const CMatrix& mat = *m_attackBoneMat;
	CVector3 pos;
	pos.x = mat.m[3][0];
	pos.y = mat.m[3][1];
	pos.z = mat.m[3][2];
	CVector3 manip;
	manip.x = mat.m[1][0];
	manip.x = mat.m[1][1];
	manip.x = mat.m[1][2];
	manip.Normalize();
	manip.Scale(0.3f);
	pos += manip;
	return { true, pos };
}

SWeaponTraceDrawInfo CTwinSword::WeaponTraceDraw()
{
	CVector3 position = *(CVector3*)m_attackBoneMat->m[3];
	CVector3 manip = *(CVector3*)m_attackBoneMat->m[2];
	manip.Normalize();
	CVector3 manip2 = manip;
	manip.Scale(0.2f);
	manip2.Scale(1.0f);
	CVector3 position2 = position + manip;
	CVector3 position3 = position + manip2;
	return { true, position2, position3 };
}