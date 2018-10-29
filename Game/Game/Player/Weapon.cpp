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
	m_position[enWeaponArrow] = {0.0f, 0.0f, -10.0f};
	m_rotation[enWeaponArrow] = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enWeaponArrow].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enWeaponArrow].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation[enWeaponArrow].Multiply(multi);

	m_attackRotation[enWeaponArrow] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackRotation[enWeaponArrow].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackRotation[enWeaponArrow].Multiply(multi);
	m_attackPosition[enWeaponArrow] = { 10.0f, 0.0f, 0.0f };


	m_position[enWeaponSword] = { 0.0f, 0.0f, -10.0f };
	m_rotation[enWeaponSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enWeaponSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enWeaponSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation[enWeaponSword].Multiply(multi);

	m_attackRotation[enWeaponSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation[enWeaponSword].Multiply(multi);
	m_attackPosition[enWeaponSword] = { 10.0f, 0.0f, 0.0f };

	m_position[enWeaponTwinSword] = { 0.0f, 0.0f, -10.0f };
	m_rotation[enWeaponTwinSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enWeaponTwinSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enWeaponTwinSword].Multiply(multi);

	m_attackRotation[enWeaponTwinSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackRotation[enWeaponTwinSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackRotation[enWeaponTwinSword].Multiply(multi);
	m_attackPosition[enWeaponTwinSword] = { 10.0f, 0.0f, 0.0f };

	m_position[enWeaponLongSword] = { 0.0f, 0.0f, -10.0f };
	m_rotation[enWeaponLongSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation[enWeaponLongSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation[enWeaponLongSword].Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation[enWeaponLongSword].Multiply(multi);

	m_attackRotation[enWeaponLongSword] = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_attackRotation[enWeaponLongSword].Multiply(multi);
	m_attackPosition[enWeaponLongSword] = { 10.0f, 0.0f, 0.0f };
}


void CWeapon::Update()
{
	if (Pad().IsTriggerButton(enButtonUp))
	{
		m_weaponState = enWeaponSword;
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		m_weaponState = enWeaponArrow;
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		m_weaponState = enWeaponTwinSword;
	}
	else if (Pad().IsTriggerButton(enButtonRight))
	{
		m_weaponState = enWeaponLongSword;
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