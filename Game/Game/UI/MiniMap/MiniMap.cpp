#include "stdafx.h"
#include "MiniMap.h"
#include "../../Player/Player.h"
#include "../../Enemy/IEnemy.h"

void CMiniMap::Init(std::list<IEnemy*> enemyList)
{
	m_camera.Init();
	m_camera.SetFar(300.0f);
	m_camera.SetNear(1.0f);
	m_camera.SetAspect((float)FrameBufferWidth() / (float)FrameBufferHeight());
	m_camera.SetAngle(CMath::DegToRad(60.0f));
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 cameraPos = playerPos;
	cameraPos.y += 20.0f;
	m_camera.SetPosition(cameraPos);
	m_camera.SetTarget(playerPos);
	m_camera.SetUp({ 0.0f, 0.0f, 1.0f });
	m_camera.Update();

	m_mapCenterPos = { 540.0f,-260.0f };

	m_miniMapTexture.Load(L"Assets/sprite/miniMap.png");
	m_miniMap.Init(&m_miniMapTexture);
	m_miniMap.SetPosition(m_mapCenterPos);
	m_miniMap.SetSize({ 180.0f,180.0f });
	m_miniMap.SetAlpha(0.8f);

	m_playerIconTexture.Load(L"Assets/sprite/player_Icon.png");
	m_playerIcon.Init(&m_playerIconTexture);
	m_playerIcon.SetPosition(m_mapCenterPos);
	m_playerIcon.SetSize({ 25.0f,25.0f });
	m_playerIconVec *= -1.0f;

	m_enemyIconTexture.Load(L"Assets/sprite/enemy_Icon.png");
	m_enemyList = enemyList;
}

void CMiniMap::Update()
{
	//プレイヤーのワールド行列からキャラクターの向きを取得
	CMatrix playerWorldMatrix = GetPlayer().GetWorldMatrix();
	CVector3 playerForward;
	playerForward.x = playerWorldMatrix.m[2][0];
	playerForward.y = 0.0f;
	playerForward.z = playerWorldMatrix.m[2][2];
	playerForward.Normalize();

	float angle = playerForward.Dot(m_playerIconVec);
	if (angle > 1.0f) {
		angle = 1.0f;
	}
	else if (angle < -1.0f) {
		angle = -1.0f;
	}
	angle = acosf(angle);

	CVector3 Cross = playerForward;
	Cross.Cross(m_playerIconVec);
	if (Cross.y > 0.0f) {
		angle *= -1.0f;
	}

	m_playerIcon.SetRotationAngle(angle);
}

void CMiniMap::Draw()
{
	m_miniMap.Draw();
	m_playerIcon.Draw();
}
