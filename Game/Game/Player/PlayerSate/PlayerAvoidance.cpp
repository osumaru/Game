#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"



void CPlayerAvoidance::Init()
{
	m_pPlayer->PlayAnimation(enPlayerAnimationAvoidance, 0.1f);
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;

}

void CPlayerAvoidance::Update()
{
	CVector3 playerPos = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];
	CVector3 moveSpeed = bonePos - m_preBonePos;
	moveSpeed.y = 0.0f;
	CCharacterController& characon = m_pPlayer->GetCharacterController();
	float gravity = characon.GetGravity();
	characon.SetMoveSpeed(moveSpeed);
	characon.SetGravity(-0.3f);
	m_preBonePos.y = playerPos.y;
	characon.SetPosition(m_preBonePos);
	m_preBonePos = bonePos;
	characon.Execute(1.0f);
	playerPos.y = characon.GetPosition().y;
	m_pPlayer->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	if (characon.GetWallCollisionObject() != nullptr)
	{
		int boneID = m_pPlayer->GetPlayerSkin().GetSkelton()->FindBone(L"Hips")->GetBoneID();
		m_pPlayer->GetAnimation().SetBoneFreezeFlg(boneID, true, true, false);
	}
	if (!GetPlayer().GetAnimation().IsPlay())
	{
		CVector3 position;
		position = GetPlayer().GetPosition();
		position.x = m_pBoneMat->m[3][0];
		position.y = m_pBoneMat->m[3][1];
		position.z = m_pBoneMat->m[3][2];
		position += m_manipVec;
		m_pPlayer->SetPosition(position);

		GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}
