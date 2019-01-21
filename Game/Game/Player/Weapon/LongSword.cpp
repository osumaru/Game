#include "LongSword.h"
#include "../Player.h"

void CLongSword::Init()
{
	m_position = { 10.0f, 60.0f, -17.0f };
	CQuaternion multi;
	m_rotation = CQuaternion::Identity;
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
	m_skinModel.LoadSpecularMap(L"Assets/modelData/LargeSword_metallic.tif");
	m_skinModel.LoadNormalmap(L"Assets/modelData/LargeSword_normal.tif");
	m_skinModel.SetSpecularPower(0.5f);


	m_maxAttackNum = 3;
	m_maxWeaponHitNum = 1;
	m_hitEffectParam = std::make_unique<SHitEffectParam[]>(m_maxAttackNum);
	m_attackAnimation = std::make_unique<EnPlayerAnimation[]>(m_maxAttackNum);
	m_combineAnimation =std::make_unique<EnPlayerAnimation[]>(m_maxAttackNum);
	m_hitEffectParam[0] = { 0.1f, 0.0f, 0.1f };
	m_hitEffectParam[1] = { 0.1f, 0.0f, 0.1f };
	m_hitEffectParam[2] = { 0.1f, 0.0f, 0.1f };
	for (int i = 0; i < m_maxAttackNum; i++)
	{
		m_attackAnimation[i] = (EnPlayerAnimation)(enPlayerAnimationLeageAttack1 + i);
		m_combineAnimation[i] = (EnPlayerAnimation)(enPlayerAnimationLeageAttackCombine1 + i);
	}
	m_stanAttack = std::make_unique<bool[]>(m_maxAttackNum);
	m_stanAttack[0] = false;
	m_stanAttack[1] = false;
	m_stanAttack[2] = true;
	
}

void CLongSword::Update()
{

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
	CVector3 xVec = *(CVector3*)m_skinModel.GetWorldMatrix().m[1];
	xVec.Normalize();
	xVec.Scale(0.1f);

	CVector3 position = *(CVector3*)m_attackBoneMat->m[3];
	CVector3 manip = *(CVector3*)m_attackBoneMat->m[2];
	manip.Normalize();
	CVector3 manip2 = manip;
	manip.Scale(0.25f);
	manip2.Scale(1.4f);

	position.Add(xVec);
	CVector3 position2 = position + manip;
	CVector3 position3 = position + manip2;
	SWeaponTraceDrawInfo infoTrace;
	infoTrace.isDraw = true;
	infoTrace.rootPos[0] = position2;
	infoTrace.pointPos[0] = position3;

	return infoTrace;
}