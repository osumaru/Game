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