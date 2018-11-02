#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "../Camera/GameCamera.h"

void CWeapon::Init(CPlayer* player)
{
	m_pPlayer = player;
	m_weaponskin[0].Load(L"Assets/modelData/Sword.cmo", NULL);
	m_weaponskin[1].Load(L"Assets/modelData/LargeSword.cmo", NULL);
	m_weaponskin[2].Load(L"Assets/modelData/LongBow.cmo", NULL);
	m_weaponskin[3].Load(L"Assets/modelData/TwinSword.cmo", NULL);
	m_boneMat = &m_pPlayer->GetPlayerSkin().FindBoneWorldMatrix(L"LeftShoulder");
	m_position[enArrow] = {0.0f, 0.0f, -10.0f};
	m_rotation[enArrow] = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enArrow].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enArrow].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation[enArrow].Multiply(multi);

	m_attackRotation[enArrow] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation[enArrow].Multiply(multi);
	m_attackPosition[enArrow] = { 10.0f, 0.0f, 0.0f };


	m_position[enSword] = { 0.0f, 0.0f, -10.0f };
	m_rotation[enSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation[enSword].Multiply(multi);

	m_attackRotation[enSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation[enSword].Multiply(multi);
	m_attackPosition[enSword] = { 10.0f, 0.0f, 0.0f };

	m_position[enTwinSword] = { 0.0f, 0.0f, -10.0f };
	m_rotation[enTwinSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enTwinSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enTwinSword].Multiply(multi);

	m_attackRotation[enTwinSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackRotation[enTwinSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackRotation[enTwinSword].Multiply(multi);
	m_attackPosition[enTwinSword] = { 10.0f, 0.0f, 0.0f };

	m_position[enLongSword] = { 0.0f, 0.0f, -10.0f };
	m_rotation[enLongSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enLongSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enLongSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation[enLongSword].Multiply(multi);

	m_attackRotation[enLongSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation[enLongSword].Multiply(multi);
	m_attackPosition[enLongSword] = { 10.0f, 0.0f, 0.0f };
}


void CWeapon::Update()
{
	if (Pad().IsTriggerButton(enButtonUp))
	{
		m_weaponState = enSword;
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		m_weaponState = enArrow;
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		m_weaponState = enTwinSword;
	}
	else if (Pad().IsTriggerButton(enButtonRight))
	{
		m_weaponState = enLongSword;
	}
	CVector3 position;
	CQuaternion rotation;
	if (m_pPlayer->GetIsAttack())
	{

		m_boneMat = &m_pPlayer->GetPlayerSkin().FindBoneWorldMatrix(L"LeftHand");
		position = m_attackPosition[m_weaponState];
		rotation = m_attackRotation[m_weaponState];
	}
	else
	{
		m_boneMat = &m_pPlayer->GetPlayerSkin().FindBoneWorldMatrix(L"LeftShoulder");
		position = m_position[m_weaponState];
		rotation = m_rotation[m_weaponState];
	}
	position.Mul(*m_boneMat);
	m_worldPos[m_weaponState] = position;
	CMatrix rotMat = *m_boneMat;
	((CVector3*)rotMat.m[0])->Div(((CVector3*)rotMat.m[0])->Length());
	((CVector3*)rotMat.m[1])->Div(((CVector3*)rotMat.m[1])->Length());
	((CVector3*)rotMat.m[2])->Div(((CVector3*)rotMat.m[2])->Length());
	rotMat.m[3][0] = 0.0f;
	rotMat.m[3][1] = 0.0f; 
	rotMat.m[3][2] = 0.0f;
	CQuaternion multi;
	multi.SetRotation(rotMat);
	multi.Multiply(rotation);
	rotation = multi;
	m_weaponskin[m_weaponState].Update(position, rotation, CVector3::One);
}

void CWeapon::Draw()
{
	const CCamera& camera = GetGameCamera().GetCamera();
	m_weaponskin[m_weaponState].Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
}