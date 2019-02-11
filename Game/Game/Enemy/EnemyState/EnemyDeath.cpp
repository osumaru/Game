#include "stdafx.h"
#include "EnemyDeath.h"
#include "../IEnemy.h"
#include "../../Item/RecoveryItem.h"
#include "../../Item/Money.h"
#include "../../Item/TreasureChest.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"

bool CEnemyDeath::Start()
{
	//死亡アニメーションを再生
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Death, 0.3f);

	//移動しない
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 speed = CVector3::Zero;
	moveSpeed.x = speed.x;
	moveSpeed.z = speed.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//プレイヤーが経験値獲得
	GetPlayer().ExpUP(m_enemy->GetStatus().exp);

	m_enemy->SetIsDead(true);

	return true;
}

void CEnemyDeath::Update()
{
	//ライトが黒くなったか
	if (m_lightSetEnd)
	{
		//お金
		CMoney* money = New<CMoney>(PRIORITY_ITEM);
		money->Init(m_enemy->GetPosition(), m_enemy->GetStatus().gold);
		//ランダムで0～9の数値を取得
		int randomNum = Random().GetRandSInt() % 10;
		//５割の確率で出す
		if (randomNum < 5)
		{
			//回復アイテム
			CRecoveryItem* recoveryItem = New<CRecoveryItem>(PRIORITY_ITEM);
			recoveryItem->Init(m_enemy->GetPosition());
		}
		//３割の確率で出す
		if (randomNum < 3)
		{
			//宝箱
			CTreasureChest* treasureChest = New<CTreasureChest>(PRIORITY_ITEM);
			//腰の座標を取得
			const CMatrix* spineMatrix = m_enemy->GetWorldMatrixSpine();
			CVector3 spinePosition;
			spinePosition.x = spineMatrix->m[3][0];
			spinePosition.y = spineMatrix->m[3][1];
			spinePosition.z = spineMatrix->m[3][2];
			treasureChest->Init(spinePosition, m_enemy->GetRotation(), false);
		}
		m_isAnimationEnd = true;
		m_enemy->EnemyListErase();
		Delete(m_enemy);
	}
	//死亡アニメーションが終わったか
	if (!m_enemy->GetAnimation().IsPlay()) 
	{
		if (!m_lightSetEnd)
		{
			//環境光の値を小さくしていく
			CLight light = m_enemy->GetSkinModel().GetLight();
			CVector4 ambientLight = light.GetAmbientLight();
			float diffuseLight = m_enemy->GetSkinModel().GetDiffuseLightPower();
			ambientLight.w -= GameTime().GetDeltaFrameTime();
			diffuseLight -= GameTime().GetDeltaFrameTime();

			if (ambientLight.w <= 0.0f)
			{
				ambientLight.w = 0.0f;
			}
			if (diffuseLight <= 0.0f)
			{
				diffuseLight = 0.0f;
			}
			if (ambientLight.w <= 0.0f && diffuseLight <= 0.0f)
			{
				m_lightSetEnd = true;
				//腰の座標を取得
				const CMatrix* spineMatrix = m_enemy->GetWorldMatrixSpine();
				CVector3 spinePosition;
				spinePosition.x = spineMatrix->m[3][0];
				spinePosition.y = spineMatrix->m[3][1];
				spinePosition.z = spineMatrix->m[3][2];
				//パーティクルエミッターの初期化
				SParticleEmittInfo particleEmitInfo;
				particleEmitInfo.filePath = L"Assets/particle/smork2.png";
				particleEmitInfo.uv = { 0.0f,0.0f,1.0f,1.0f };
				particleEmitInfo.width = 0.5f;
				particleEmitInfo.height = 0.5f;
				particleEmitInfo.emitterLifeTime = 0.1f;
				particleEmitInfo.emitterPosition = spinePosition;
				particleEmitInfo.emittIntervalTime = 0.0f;
				particleEmitInfo.gravity = { 0.0f,0.0f,0.0f };
				particleEmitInfo.moveSpeed = { 0.0f,0.2f,0.0f };
				particleEmitInfo.lifeTime = 2.0f;
				particleEmitInfo.randomMoveSpeed = { 0.0f,0.0f,0.0f };
				particleEmitInfo.randomPosition = { 0.6f, 0.6f, 0.6f };
				particleEmitInfo.particleNum = 10;
				particleEmitInfo.fadeOutTime = 2.0f;
				particleEmitInfo.alphaBlendState = enAlphaBlendStateTranslucent;
				particleEmitInfo.isFirstTimeRandom = false;
				CParticleEmitter* particleEmitter = New<CParticleEmitter>(PRIORITY_PARTICLE);
				particleEmitter->Init(particleEmitInfo, &GetGameCamera().GetCamera());
			}

			light.SetAmbientLight(ambientLight);
			m_enemy->GetSkinModel().SetLight(light);
			m_enemy->GetSkinModel().SetDiffuseLightPower(diffuseLight);
		}
	}
}
