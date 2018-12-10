#include "LongSword.h"
#include "../Player.h"

void CLongSword::Init()
{
	m_position = { 0.0f, 0.0f, -10.0f };
	m_rotation = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation.Multiply(multi);

	m_attackRotation = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation.Multiply(multi);
	m_attackPosition = { -10.0f, 0.0f, 0.0f };
	m_skinModel.Load(L"Assets/modelData/LargeSword.cmo", NULL);

	m_attackAnimation = new EnPlayerAnimation[3];
	m_attackAnimation[0] = enPlayerAnimationLeageAttack1;
	m_attackAnimation[1] = enPlayerAnimationLeageAttack2;
	m_attackAnimation[2] = enPlayerAnimationLeageAttack3;
	m_combineAnimation = new EnPlayerAnimation[3];
	m_combineAnimation[0] = enPlayerAnimationLeageAttackCombine1;
	m_combineAnimation[1] = enPlayerAnimationLeageAttackCombine2;
	m_combineAnimation[2] = enPlayerAnimationLeageAttackCombine3;
	m_stanAttack = new bool[3];
	m_stanAttack[0] = false;
	m_stanAttack[1] = false;
	m_stanAttack[2] = true;
}

SWeaponEnemyAttackInfo CLongSword::EnemyAttackPositionDecide()
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

SWeaponTraceDrawInfo CLongSword::WeaponTraceDraw()
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