#include "stdafx.h"
#include "MiniMap.h"
#include "../../Player/Player.h"
#include "../../Enemy/IEnemy.h"
#include "../../Camera/GameCamera.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"

CMiniMap::CMiniMap()
{
}

CMiniMap::~CMiniMap()
{
}

void CMiniMap::Init()
{
	m_mapCenterPos = { 540.0f,-260.0f };
	//ミニマップを初期化
	m_miniMapTexture = TextureResource().LoadTexture(L"Assets/sprite/miniMap.png");
	m_miniMap.Init(m_miniMapTexture);
	m_miniMap.SetPosition(m_mapCenterPos);
	m_miniMap.SetSize({ 180.0f,180.0f });
	m_miniMap.SetAlpha(0.8f);
	//プレイヤーアイコンを初期化
	m_playerIconTexture = TextureResource().LoadTexture(L"Assets/sprite/player_Icon.png");
	m_playerIcon.Init(m_playerIconTexture);
	m_playerIcon.SetPosition(m_mapCenterPos);
	m_playerIcon.SetSize({ 15.0f,15.0f });
	//エネミーアイコンを初期化
	m_enemyIconTexture = TextureResource().LoadTexture(L"Assets/sprite/enemy_Icon.png");
	m_enemyList = &GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
	for (int i = 0; i < m_enemyList->size(); i++) {
		m_enemyIcon.emplace_back(std::make_unique<CSprite>());
		m_enemyIcon[i]->Init(m_enemyIconTexture);
		m_enemyIcon[i]->SetPosition(m_mapCenterPos);
		m_enemyIcon[i]->SetSize({ 10.0f,10.0f });
		m_enemyIcon[i]->SetAlpha(0.8f);
	}
}

void CMiniMap::Update()
{
	//カメラの上方向を設定
	CVector3 cameraUp = GetGameCamera().GetCamera().GetTarget() - GetGameCamera().GetCamera().GetPosition();
	cameraUp.y = 0.0f;
	//カメラの注視点を設定
	CVector3 target = GetPlayer().GetPosition();
	//カメラの座標を設定
	CVector3 cameraPos = target;
	cameraPos.y += 20.0f;
	//ビュー行列を計算
	CMatrix viewMatrix;
	viewMatrix.MakeLookAt(cameraPos, target, cameraUp);
	//プロジェクション行列を計算
	CMatrix projectionMatrix;
	projectionMatrix.MakeOrthoProjectionMatrix(100.0f, 100.0f, 1.0f, 100.0f);

	//敵アイコンの処理
	{
		m_enemyList = &GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		int idx = 0;
		for (auto& enemy : *m_enemyList)
		{
			CVector3 toCameraXZ = cameraPos - enemy->GetPosition();
			toCameraXZ.y = 0.0f;
			float length = toCameraXZ.Length();
			if (length <= 50.0f) {
				//ビュー変換
				CVector4 viewPosition;
				viewPosition.Set(enemy->GetPosition());
				viewMatrix.Mul(viewPosition);
				//プロジェクション変換
				CVector4 projectionPosition = viewPosition;
				projectionMatrix.Mul(projectionPosition);
				projectionPosition = projectionPosition / projectionPosition.w;
				//スクリーン変換
				CVector2 screenPosition;
				screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * m_miniMap.GetSize().x - (m_miniMap.GetSize().x / 2.0f);
				screenPosition.y = (1.0f + projectionPosition.y) / 2.0f * m_miniMap.GetSize().y - (m_miniMap.GetSize().y / 2.0f);
				screenPosition += m_mapCenterPos;
				//敵のアイコンの座標を更新
				m_enemyIcon[idx]->SetPosition(screenPosition);
				m_enemyIcon[idx]->SetIsDraw(true);
			}
			else {
				m_enemyIcon[idx]->SetIsDraw(false);
			}
			idx++;
		}
	}

	//プレイヤーアイコンの処理
	{
		//プレイヤーのワールド行列からキャラクターの向きを取得
		CMatrix playerWorldMatrix = GetPlayer().GetSkinmodel().GetWorldMatrix();
		CVector3 playerForward;
		playerForward.x = playerWorldMatrix.m[2][0];
		playerForward.y = 0.0f;
		playerForward.z = playerWorldMatrix.m[2][2];
		playerForward.Normalize();
		//プレイヤーアイコンの向きを設定
		CVector3 playerIconVec = cameraUp;
		playerIconVec.Normalize();
		float angle = playerForward.Dot(playerIconVec);
		if (angle > 1.0f) {
			angle = 1.0f;
		}
		else if (angle < -1.0f) {
			angle = -1.0f;
		}
		angle = acosf(angle);
		//右回転か左回転か決める
		CVector3 Cross = playerForward;
		Cross.Cross(playerIconVec);
		if (Cross.y > 0.0f) {
			angle *= -1.0f;
		}
		//プレイヤーアイコンを回転させる
		m_playerIcon.SetRotationAngle(angle);
	}
}

void CMiniMap::PostAfterDraw()
{
	m_miniMap.Draw();
	for (int i = 0; i < m_enemyList->size(); i++) {
		m_enemyIcon[i]->Draw();
	}
	m_playerIcon.Draw();
}
