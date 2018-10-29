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
	m_position = {0.0f, 0.0f, -10.0f};
	m_rotation = CQuaternion::Identity;
	CQuaternion multi;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisZ, 90.0f);
	m_rotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	m_rotation.Multiply(multi);

	m_attackRotation = CQuaternion::Identity;
	multi.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_attackRotation.Multiply(multi);
	multi.SetRotationDeg(CVector3::AxisY, 90.0f);
	m_attackRotation.Multiply(multi);
	//multi.SetRotationDeg(CVector3::AxisX, -20.0f);
	//m_attackRotation.Multiply(multi);
	m_attackPosition = { 10.0f, 0.0f, 0.0f };
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
	else if (Pad().IsTriggerButton(enButtonRight))
	{
		m_weaponState = enWeaponTwinSword;
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		m_weaponState = enWeaponLongSword;
	}
	CVector3 position = m_position;
	CQuaternion rotation = m_rotation;
	if (m_pPlayer->GetIsAttack())
	{

		m_boneMat = &m_pPlayer->GetPlayerSkin().FindBoneWorldMatrix(L"LeftHand");
		position = m_attackPosition;
		rotation = m_attackRotation;
	}
	else
	{
		m_boneMat = &m_pPlayer->GetPlayerSkin().FindBoneWorldMatrix(L"LeftShoulder");
		position = m_position;
		rotation = m_rotation;
	}
	position.Mul(*m_boneMat);
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