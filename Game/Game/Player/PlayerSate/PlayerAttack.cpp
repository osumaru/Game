#include "stdafx.h"
#include "PlayerAttack.h"
#include "../Player.h"
#include "../../Scene/GameScene.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
#include "../../Scene/SceneManager.h"
#include "../../Enemy/Boss/Maw.h"
#include "../../Camera/GameCamera.h"
#include "../../Command/Command.h"

CPlayerAttack::CPlayerAttack()
{

}

void CPlayerAttack::Init()
{
	IPlayerState::Init();
	m_attackAnimation = GetPlayer().GetWeaponManager().GetWeapon()->GetAttackAnimation();
	m_combineAnimation = GetPlayer().GetWeaponManager().GetWeapon()->GetCombineAnimation();
	m_stanAttack = GetPlayer().GetWeaponManager().GetWeapon()->GetStanAttack();
	m_maxAttackNum = GetPlayer().GetWeaponManager().GetWeapon()->GetMaxAttackNum();
	m_maxWeaponHitNum = GetPlayer().GetWeaponManager().GetWeapon()->GetMaxWeaponHitNum();
	for (int i = 0; i < Map::AREA_PARTITION_NUM; i++)
	{
		for (int j = 0; j < Map::AREA_PARTITION_NUM; j++)
		{
			std::list<MapChip*>& mapChips = GetSceneManager().GetMap()->GetMapChips(i, j);
			//エネミーのリストを取得
			for (auto& mapChip : mapChips)
			{
				IEnemy* enemy = dynamic_cast<IEnemy*>(mapChip);
				if (enemy != nullptr)
				{
					bool* damagePossible = enemy->IsDamagePossible();
					for (int i = 0; i < m_maxWeaponHitNum; i++)
					{
						damagePossible[0] = true;
						damagePossible[1] = true;
					}
				}
			}
		}
	}

	if (&GetMaw())
	{
		GetMaw().SetIsDamagePossible(true);
	}
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_attackCount = 0;
	m_isContinuationAttack = false;
	m_pPlayerGetter->GetAnimation().Play(m_attackAnimation[m_attackCount], 0.2f);	
	m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
	m_pBoneMat = &GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Hips");
	CVector3 bonePos = { m_pBoneMat->m[3][0], m_pBoneMat->m[3][1], m_pBoneMat->m[3][2] };
	m_pPlayer->GetWeaponManager().SetIsAttack(true);
	m_pPlayer->GetWeaponManager().GetWeapon()->WeaponTraceDrawStart();
	m_rotationDirectionVector = CVector3::Zero;
}

void CPlayerAttack::Update()
{

	//攻撃中に攻撃の入力がされた場合は連撃に移行する
	if (Pad().IsTriggerButton(enButtonX) && !m_isContinuationAttack && m_attackCount < m_maxAttackNum - 1)
	{
		m_isContinuationAttack = true;
	}

	Move();
	m_pPlayer->GetWeaponManager().GetWeapon(m_pPlayer->GetWeaponManager().GetCurrentState())->EnemyAttack();

	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance)) {
		m_pPlayer->SetDefferdCommand(new AvoidanceCommand(&GetPlayer()));
	}
	else if(m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateSky))
	{
		m_pPlayer->GetWeaponManager().SetIsAttack(false); 
		m_pPlayer->SetCommand(new SkyCommand(&GetPlayer()));
		return;
	}
	m_pPlayer->SetStanAttack(m_stanAttack[m_attackCount]);

	Lerp();

	m_pPlayer->GetWeaponManager().SetAttackCount(m_attackCount);

	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		CVector3 bonePos;
		bonePos.x = m_pBoneMat->m[3][0];
		bonePos.y = m_pBoneMat->m[3][1];
		bonePos.z = m_pBoneMat->m[3][2];
		CVector3 position = bonePos;
		position.y = m_pPlayer->GetPosition().y;
		m_pPlayerGetter->SetPosition(position);
		m_pPlayer->GetWeaponManager().SetIsAttackCheck(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
		m_pPlayer->SetCommand(new DamageCommand(&GetPlayer()));
		return;
	}
	else if(m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStun))
	{
		CVector3 bonePos;
		bonePos.x = m_pBoneMat->m[3][0];
		bonePos.y = m_pBoneMat->m[3][1];
		bonePos.z = m_pBoneMat->m[3][2];
		CVector3 position = bonePos;
		position.y = m_pPlayer->GetPosition().y;
		m_pPlayerGetter->SetPosition(position);
		m_pPlayer->GetWeaponManager().SetIsAttackCheck(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
		m_pPlayer->SetCommand(new StunCommand(&GetPlayer()));
		return;
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDied))
	{
		CVector3 bonePos;
		bonePos.x = m_pBoneMat->m[3][0];
		bonePos.y = m_pBoneMat->m[3][1];
		bonePos.z = m_pBoneMat->m[3][2];
		CVector3 position = bonePos;
		position.y = m_pPlayer->GetPosition().y;
		m_pPlayerGetter->SetPosition(position);
		m_pPlayer->GetWeaponManager().SetIsAttackCheck(false);
		m_pPlayer->GetWeaponManager().SetIsAttack(false);
		m_pPlayer->SetCommand(new DiedCommand(m_pPlayer));
		return;
	}

	//攻撃アニメーションが終わった時の処理
	if (!m_isStateTransition && !m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_isStateTransition = true;
		CVector3 areaPos = m_pPlayer->GetPosition();
		Map* map = GetSceneManager().GetMap();
		int areaPosX = map->GetAreaPosX(areaPos);
		int areaPosY = map->GetAreaPosY(areaPos);
		std::list<MapChip*>& mapChips = map->GetMapChips(areaPosX, areaPosY);
		//エネミーのリストを取得
		for (auto& mapChip : mapChips)
		{
			IEnemy* enemy = dynamic_cast<IEnemy*>(mapChip);
			if (enemy != nullptr)
			{
				bool* damagePossible = enemy->IsDamagePossible();
				for (int i = 0; i < m_maxWeaponHitNum; i++)
				{
					damagePossible[0] = true;
					damagePossible[1] = true;
				}
			}
		}
		if (&GetMaw())
		{
			GetMaw().SetIsDamagePossible(true);
		}

		CVector3 bonePos;
		bonePos.x = m_pBoneMat->m[3][0];
		bonePos.y = m_pBoneMat->m[3][1];
		bonePos.z = m_pBoneMat->m[3][2];
		//連続攻撃していた
		if (m_isContinuationAttack)
		{
			m_attackCount++;
			CVector3 position = m_pPlayer->GetPosition();
			position = bonePos;
			position.y = m_pPlayerGetter->GetCharacterController().GetPosition().y;
			m_pPlayerGetter->SetPosition(position);

			m_isContinuationAttack = false;
			m_pPlayerGetter->GetAnimation().Play(m_attackAnimation[m_attackCount]);
			m_pPlayerGetter->GetAnimation().Update(0.0f);
			m_pPlayer->GetWeaponManager().GetWeapon()->WeaponTraceDrawStart();

			m_isStateTransition = false;
			Rotation();
		}
		else
		{
			m_pPlayer->GetWeaponManager().SetIsAttack(false);
			CVector3 position;
			position = bonePos;
			position.y = m_pPlayer->GetPosition().y;
			m_pPlayerGetter->SetPosition(position);

			m_pPlayerGetter->GetAnimation().Play(m_combineAnimation[m_attackCount]);
			m_pPlayerGetter->GetAnimation().Update(0.0f);
			m_pPlayerGetter->SkinModelUpdate();
			m_pPlayer->GetWeaponManager().SetDrawingWeapon(true);
			if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
			{
				//走りアニメーション
				m_pPlayer->SetCommand(new RunCommand(&GetPlayer()));
			}
			else
			{
				m_pPlayer->SetCommand(new StandCommand(&GetPlayer()));

			}
		}
	}
}

void CPlayerAttack::Move()
{
	CVector3 playerPos = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];


	CCharacterController& characon = m_pPlayerGetter->GetCharacterController();
	//剛体の座標を保存
	CVector3 rigidPos = characon.GetPosition();
	bonePos.y = characon.GetPosition().y;
	characon.SetPosition(bonePos);
	//プレイヤーののボーン座標からプレイヤーの座標までのベクトルを作成
	CVector3 boneDistance = playerPos - bonePos;
	characon.DynamicExecute();

	rigidPos = characon.GetPosition();
	//衝突解決した座標にさっき作成したベクトルを足す
	playerPos = rigidPos + boneDistance;
	//プレイヤーと剛体の座標を更新
	m_pPlayerGetter->SetPosition(playerPos);
	characon.SetMoveSpeed(CVector3::Zero);
	//剛体の座標を戻す
	characon.SetPosition(rigidPos);
}

void CPlayerAttack::Rotation()
{
	//腰のボーンの座標を中心にプレイヤーを回転させる
	//カメラからの移動方向
	const CCamera& gameCamera = GetGameCamera().GetCamera();
	CVector3 frontVec = gameCamera.GetTarget() - gameCamera.GetPosition();
	frontVec.y = 0.0f;
	frontVec.Normalize();
	CVector3 rightVec;
	rightVec.Cross(CVector3::AxisY, frontVec);
	rightVec.Normalize();
	CVector3 moveSpeed = m_pPlayerGetter->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	const float speed = 1.0f;
	moveSpeed += frontVec * Pad().GetLeftStickY()*speed;
	moveSpeed += rightVec * Pad().GetLeftStickX()*speed;


	CMatrix pMat = m_pPlayer->GetSkinmodel().GetWorldMatrix();
	//プレイヤーの前方向
	CVector3 playerFront;
	playerFront.x = pMat.m[2][0];
	playerFront.y = 0.0f;
	playerFront.z = pMat.m[2][2];
	playerFront.Normalize();

	if (moveSpeed.x == 0.0f && moveSpeed.z == 0.0f)
	{
		moveSpeed.x = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][0];
		moveSpeed.z = m_pPlayer->GetSkinmodel().GetWorldMatrix().m[2][2];
	}
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();
	float rad = moveSpeed.Dot(playerFront);
	if (1.0f <= rad)
	{
		rad = 1.0f;
	}
	if (rad <= -1.0f)
	{
		rad = -1.0f;
	}
	rad = acosf(rad);
	CVector3 judgeAxis;
	judgeAxis.Cross(moveSpeed, playerFront);
	if (0.0f < judgeAxis.y)
	{
		rad = -rad;
	}

	CQuaternion rot=CQuaternion::Identity;
	rot.SetRotation(CVector3::AxisY, rad);
	CMatrix rotMat=CMatrix::Identity;
	rotMat.MakeRotationFromQuaternion(rot);

	CQuaternion pRot = m_pPlayerGetter->GetRotation();
	//腰を中心にしたクオータニオンとプレイヤーのやつの積
	pRot.Multiply(rot);
	m_addRot = pRot;
	m_rotationDirectionVector = moveSpeed;
}

void CPlayerAttack::Lerp()
{

	if (m_rotationDirectionVector.LengthSq() < 0.01f)
	{
		//座標更新されていない
		return;
	}
	//回転の線形補完
	CQuaternion rotation = m_pPlayerGetter->GetRotation();
	float slerp = 0.3f;
	rotation.Slerp(slerp, rotation, m_addRot);
	m_pPlayerGetter->SetRotation(rotation);
	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(rotation);
	//座標の線形補完
	CVector3 playerFront;
	CMatrix mat = m_pPlayer->GetSkinmodel().GetWorldMatrix();
	playerFront.x = mat.m[2][0];
	playerFront.y = 0.0f;
	playerFront.z = mat.m[2][2];
	playerFront.Normalize();
	float rad = m_rotationDirectionVector.Dot(playerFront);
	rad = max(-1.0f, min(1.0f, rad));
	rad = acosf(rad);
	CVector3 judgeAxis;
	judgeAxis.Cross(m_rotationDirectionVector, playerFront);
	if (0.0f < judgeAxis.y)
	{
		rad = -rad;
	}
	
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, rad);
	multi.Slerp(slerp, CQuaternion::Identity, multi);
	rotMat.MakeRotationFromQuaternion(multi);
	CVector3 position = m_pPlayer->GetPosition();
	CVector3 bonePos;
	bonePos.x = m_pBoneMat->m[3][0];
	bonePos.y = m_pBoneMat->m[3][1];
	bonePos.z = m_pBoneMat->m[3][2];
	CVector3 manip = position - bonePos;
	rotMat.Mul(manip);
	position = bonePos + manip;
	CVector3 rigidPos = m_pPlayerGetter->GetCharacterController().GetPosition();
	m_pPlayerGetter->SetPosition(position);
	m_pPlayerGetter->GetCharacterController().SetPosition(rigidPos);
}
