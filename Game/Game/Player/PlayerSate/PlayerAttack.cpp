#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"

CPlayerAttack::CPlayerAttack()
{
	m_attackAnimation[0] = enPlayerAnimationAttack;
	m_attackAnimation[1] = enPlayerAnimationAttack2;
	m_attackAnimation[2] = enPlayerAnimationAttack3;
}

void CPlayerAttack::Init()
{

	m_pPlayer->SetMoveSpeed(CVector3::Zero);
	m_attackCount = 0;
	m_isContinuationAttack = false;
	m_animetionFrame = 0.0f;
	m_pPlayer->PlayAnimation(m_attackAnimation[m_attackCount], 0.2f);	
	m_pPlayer->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetPlayerSkin().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;
}

void CPlayerAttack::Update()
{
	m_animetionFrame += GameTime().GetDeltaFrameTime();
	if (m_animetionFrame > 0.3f)
	{
		m_pPlayer->SetIsAttack(true);
	}
	//攻撃中に攻撃の入力がされた場合は連撃に移行する
	if (Pad().IsTriggerButton(enButtonRightTrigger) && !m_isContinuationAttack && m_attackCount < MAX_ATTACK_NUM - 1)
	{
		m_isContinuationAttack = true;
		m_attackCount++;
	}
	//プレイヤーの前のフレームのボーンの座標から今のボーンの座標をレイテストしてめり込んでいれば押し戻す
	CVector3 playerPos = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];

	//前のフレームとの座標と今の座標を引いて移動量を計算
	CVector3 moveSpeed = bonePos - m_preBonePos;
	moveSpeed.y = 0.0f;
	CCharacterController& characon = m_pPlayer->GetCharacterController();
	float gravity = characon.GetGravity();
	characon.SetGravity(-0.3f);
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
	m_pPlayer->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	m_preBonePos = bonePos;

	//攻撃アニメーションが終わった時の処理
	if (!m_pPlayer->GetAnimation().IsPlay())
	{
		//攻撃モーション中はダメージモーションをさせない
		if (m_isContinuationAttack)
		{
			m_isContinuationAttack = false;
			m_animetionFrame = 0.0f;
			m_pPlayer->PlayAnimation(m_attackAnimation[m_attackCount], 0.2f);
		}
		else
		{
			m_pPlayer->SetIsAttack(false);
			CVector3 position;
			position = bonePos;
			position += m_manipVec;
			position.y = playerPos.y;
			m_pPlayer->SetPosition(position);

			m_pPlayer->SetInterval(false);
			GetPlayer().GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);
			if (Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0)
			{
				//走りアニメーション
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetPlayerStateMachine().SetState(CPlayerState::enPlayerStateStand);

			}
		}
	}
}
