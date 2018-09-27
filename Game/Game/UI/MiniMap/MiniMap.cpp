#include "stdafx.h"
#include "MiniMap.h"
#include "../../Player/Player.h"
#include "../../Enemy/IEnemy.h"
#include "../../Map/Map.h"`
#include "../../Scene/SceneManager.h"

void CMiniMap::Init()
{
	m_miniMapTexture.Load(L"Assets/sprite/miniMap.png");
	m_miniMap.Init(&m_miniMapTexture);
	m_miniMap.SetPosition({ 540.0f, -260.0f });
	m_miniMap.SetSize({ 180.0f,180.0f });
	m_miniMap.SetAlpha(0.8f);

	m_playerIconTexture.Load(L"Assets/sprite/player_Icon.png");
	m_playerIcon.Init(&m_playerIconTexture);
	m_playerIcon.SetPosition({ 540.0f, -260.0f });
	m_playerIcon.SetSize({ 25.0f,25.0f });

	m_miniMap.SetAlpha(0.8f);
	m_playerIconVec *= -1.0f;
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
