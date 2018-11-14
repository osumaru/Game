#include "stdafx.h"
#include "PlayerAvoidance.h"
#include "../Player.h"



void CPlayerAvoidance::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationAvoidance, 0.1f);
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;
	m_pPlayerGetter->SetIsInvincible(true);
}

void CPlayerAvoidance::Update()
{
	Move();
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		CVector3 position;
		position = m_preBonePos;
		position += m_manipVec;
		m_pPlayerGetter->SetPosition(position);
		m_pPlayerGetter->SetIsInvincible(false);
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationAvoidanceCombine);
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
}

void CPlayerAvoidance::Move()
{
	//プレイヤーの前のフレームのボーンの座標から今のボーンの座標をレイテストしてめり込んでいれば押し戻す
	CVector3 playerPos = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];

	//前のフレームとの座標と今の座標を引いて移動量を計算
	CVector3 moveSpeed = bonePos - m_preBonePos;
	moveSpeed.y = 0.0f;
	CCharacterController& characon = m_pPlayerGetter->GetCharacterController();
	float gravity = characon.GetGravity();
	characon.SetGravity(-0.1f);
	//高さをプレイヤ―の座標でそろえる
	m_preBonePos.y = playerPos.y;
	characon.SetMoveSpeed(moveSpeed);
	characon.SetPosition(m_preBonePos);
	characon.Execute(1.0f);
	//何かに当たっていればプレイヤーの座標を動かしてアニメーションの移動量を打ち消す
	if (characon.GetWallCollisionObject() != nullptr)
	{
		CVector3 movePos = characon.GetPosition() - bonePos;
		movePos.y = 0.0f;
		//CVector3 playerFront;
		//playerFront.x = m_pPlayer->GetWorldMatrix().m[2][0];
		//playerFront.y = m_pPlayer->GetWorldMatrix().m[2][1];
		//playerFront.z = m_pPlayer->GetWorldMatrix().m[2][2];
		//if (playerFront.Dot(movePos) < 0.0f)
		//{
			playerPos += movePos;
		//}
	}
	playerPos.y = characon.GetPosition().y;
	m_pPlayerGetter->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	m_preBonePos = bonePos;
}