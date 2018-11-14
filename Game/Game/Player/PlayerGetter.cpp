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

void CPlayerGetter::SetPosition(const CVector3& pos)
{
	m_pPlayer->m_characterController.SetPosition(pos);
}

void CPlayerGetter::SetMoveSpeed(const CVector3& moveSpeed)
{
	m_pPlayer->m_characterController.SetMoveSpeed(moveSpeed);
}

void CPlayerGetter::SetIsDied(bool isDied)
{
	m_pPlayer->m_isDied = isDied;
}

void CPlayerGetter::SetIsAttack(bool isAttack)
{
	m_pPlayer->m_isAttack = isAttack;
}

const CVector3& CPlayerGetter::GetMoveSpeed()
{
	return m_pPlayer->m_characterController.GetMoveSpeed();
}