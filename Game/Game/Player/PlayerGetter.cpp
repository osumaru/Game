#include "stdafx.h"
#include "PlayerGetter.h"
#include "Player.h"


CWireAction& CPlayerGetter::GetWireAction()
{
	return m_pPlayer->m_wireAction;
}

void CPlayerGetter::SetIsInvincible(bool isInvincible)
{
	m_pPlayer->m_isInvinsible = isInvincible;
}

CAnimation& CPlayerGetter::GetAnimation()
{
	return m_pPlayer->m_animation;
}

CCharacterController& CPlayerGetter::GetCharacterController()
{
	return m_pPlayer->m_characterController;
}

void CPlayerGetter::DamageStateReset()
{
	m_pPlayer->m_isDamege = false;
}

void CPlayerGetter::StanDamageStateReset()
{
	m_pPlayer->m_isStanDamage = false;
}

void CPlayerGetter::SetPosition(const CVector3& pos)
{
	m_pPlayer->m_characterController.SetPosition(pos);
}

const CQuaternion& CPlayerGetter::GetRotation()
{
	return m_pPlayer->m_rotation;
}

void CPlayerGetter::SetRotation(const CQuaternion & rotation)
{
	m_pPlayer->m_rotation = rotation;
}

void CPlayerGetter::SetMoveSpeed(const CVector3& moveSpeed)
{
	m_pPlayer->m_characterController.SetMoveSpeed(moveSpeed);
}

void CPlayerGetter::SetIsDied(bool isDied)
{
	m_pPlayer->m_isDied = isDied;
}

const CVector3& CPlayerGetter::GetMoveSpeed()
{
	return m_pPlayer->m_characterController.GetMoveSpeed();
}

void CPlayerGetter::SetStickDir(const CVector3 & stickDir)
{
	m_stickDir = stickDir;
}

const CVector3& CPlayerGetter::GetStickDir()
{
	return m_stickDir;
}

void CPlayerGetter::SetDamageEnemyPos(const CVector3& position)
{
	m_damageEnemyPos = position;
}

const CVector3& CPlayerGetter::GetDamageEnemyPos()
{
	return m_damageEnemyPos;
}

CWireDraw & CPlayerGetter::GetWireDraw()
{
	return m_pPlayer->m_wireDraw;
}

void CPlayerGetter::SkinModelUpdate()
{
	m_pPlayer->m_skinmodel.Update(m_pPlayer->m_position, m_pPlayer->m_rotation, CVector3::One, true);
}