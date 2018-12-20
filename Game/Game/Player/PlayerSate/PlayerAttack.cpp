#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"
#include "../../Scene/GameScene.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
#include "../../Scene/SceneManager.h"
#include "../../Enemy/Maw.h"
#include "../../Camera/GameCamera.h"

CPlayerAttack::CPlayerAttack()
{

}

void CPlayerAttack::Init()
{
	m_attackAnimation = GetPlayer().GetWeaponManager().GetWeapon()->GetAttackAnimation();
	m_combineAnimation = GetPlayer().GetWeaponManager().GetWeapon()->GetCombineAnimation();
	m_stanAttack = GetPlayer().GetWeaponManager().GetWeapon()->GetStanAttack();
	m_maxAttackNum = GetPlayer().GetWeaponManager().GetWeapon()->GetMaxAttackNum();

	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_attackCount = 0;
	m_isContinuationAttack = false;
	m_pPlayerGetter->GetAnimation().Play(m_attackAnimation[m_attackCount], 0.2f);	
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_manipVec = m_pPlayer->GetPosition() - bonePos;
	m_preBonePos = bonePos;
	m_pPlayer->GetWeaponManager().SetIsAttack(true);
	m_pPlayer->GetWeaponManager().GetWeapon()->WeaponTraceDrawStart();
	m_isPreDodge = false;
}

void CPlayerAttack::Update()
{

	//攻撃中に攻撃の入力がされた場合は連撃に移行する
	if (Pad().IsTriggerButton(enButtonX) && !m_isContinuationAttack && m_attackCount < m_maxAttackNum/*MAX_ATTACK_NUM*/ - 1)
	{
		m_isContinuationAttack = true;
		m_attackCount++;
	}

	Move();
	m_pPlayer->GetWeaponManager().GetWeapon(m_pPlayer->GetWeaponManager().GetCurrentState())->EnemyAttack();

	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance)) {
		m_isPreDodge = true;
	}

	m_pPlayer->SetStanAttack(m_stanAttack[m_attackCount]);

	//攻撃アニメーションが終わった時の処理
	if (!m_pPlayerGetter->GetAnimation().IsPlay())
	{
		//エネミーのリストを取得
		for (const auto& enemys : GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
		{
			enemys->SetIsDamagePossible(true);
			enemys->SetAttackWeapon(EnAttackWeapon::enAttackWeaponNone);
		}
		//攻撃モーション中はダメージモーションをさせない
		if (m_isContinuationAttack)
		{
			m_isContinuationAttack = false;
			m_pPlayerGetter->GetAnimation().Play(m_attackAnimation[m_attackCount], 0.2f);
			m_pPlayer->GetWeaponManager().GetWeapon()->WeaponTraceDrawStart();

			Rotation();
		}
		else
		{
			m_pPlayer->GetWeaponManager().SetIsAttack(false);
			CVector3 position;
			position = m_preBonePos;
			position += m_manipVec;
			position.y = m_pPlayerGetter->GetCharacterController().GetPosition().y;
			m_pPlayerGetter->SetPosition(position);

			m_pPlayerGetter->GetAnimation().Play(m_combineAnimation[m_attackCount]);
			if (m_isPreDodge)
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
			}
			else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
			{
				//走りアニメーション
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
			}
			else
			{
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);

			}
		}
	}
}

void CPlayerAttack::Move()
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
		CVector3 playerFront;
		playerFront.x = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][0];
		playerFront.y = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][1];
		playerFront.z = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][2];
		if (playerFront.Dot(movePos) < 0.0f)
		{
			playerPos += movePos;
		}
	}
	playerPos.y = characon.GetPosition().y;
	m_pPlayerGetter->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	characon.SetGravity(gravity);
	m_preBonePos = bonePos;
}

void CPlayerAttack::Rotation()
{
	const CCamera& gameCamera = GetGameCamera().GetCamera();
	CMatrix spineMat = m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 spineVec;
	spineVec.x = spineMat.m[3][0];
	spineVec.y = spineMat.m[3][1];
	spineVec.z = spineMat.m[3][2];
	CVector3 frontVec = gameCamera.GetTarget() - gameCamera.GetPosition();
	frontVec.y = 0.0f;
	frontVec.Normalize();
	CVector3 rightVec;
	rightVec.Cross(CVector3::AxisY, frontVec);
	rightVec.Normalize();
	CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	const float speed = 4.0f;
	moveSpeed += frontVec * Pad().GetLeftStickY()*speed;
	moveSpeed += rightVec * Pad().GetLeftStickX()*speed;
	////moveSpeed.Normalize();
	m_pPlayerGetter->SetMoveSpeed(moveSpeed);
	//
	////CVector3 moveSpeed = moveSpeed;//m_pPlayerGetter->GetMoveSpeed();
	//CVector3 playerFront = frontVec;
	//if (moveSpeed.x == 0.0f && moveSpeed.z == 0.0f)
	//{
	//	moveSpeed.x = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][0];
	//	moveSpeed.z = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][2];
	//}
	//moveSpeed.y = 0.0f;
	//moveSpeed.Normalize();
	//float rad = moveSpeed.Dot(playerFront);
	//if (1.0f <= rad)
	//{
	//	rad = 1.0f;
	//}
	//if (rad <= -1.0f)
	//{
	//	rad = -1.0f;
	//}
	//rad = acosf(rad);
	//CVector3 judgeAxis;
	//judgeAxis.Cross(moveSpeed, playerFront);
	//if (0.0f < judgeAxis.y)
	//{
	//	rad = -rad;
	//}

	////m_pPlayerGetter->SetRotation(CVector3::AxisY, rad);
	//CQuaternion rot;
	//rot.SetRotation(CVector3::AxisY,rad);
	////m_pPlayerGetter->SetRotation(rot);
	//CMatrix rotMat;
	//rotMat.MakeRotationFromQuaternion(rot);
	////CMatrix spineMat=m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	////CVector3 spineVec;
	//spineVec.x=spineMat.m[3][0];
	//spineVec.y=spineMat.m[3][1];
	//spineVec.z=spineMat.m[3][2];
	//CVector3 animPos= spineVec- m_pPlayer->GetPosition();
	//rotMat.Mul(animPos);
	//animPos.Add(spineVec);

	//m_pPlayerGetter->SetPosition(animPos);


	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

}

