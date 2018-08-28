#include "stdafx.h"
#include "MiniMap.h"

namespace {
	//ミニマップ
	const Vector2 miniMapPosition = { 540.0f, -260.0f };
	const Vector2 miniMapSize = { 180.0f,180.0f };
	//プレイヤーアイコン
	const Vector2 playerIconSize = { 50.0f,50.0f };
}

void MiniMap::Init()
{
	m_miniMapTexture.Load(L"Assets/sprite/miniMap.png");
	m_miniMap.Init(&m_miniMapTexture);
	m_miniMap.SetPosition(miniMapPosition);
	m_miniMap.SetSize(miniMapSize);

	m_playerIconTexture.Load(L"Assets/sprite/player_Icon.png");
	m_playerIcon.Init(&m_playerIconTexture);
	m_playerIcon.SetPosition(miniMapPosition);
	m_playerIcon.SetSize(playerIconSize);
}

void MiniMap::Update()
{
}

void MiniMap::Draw()
{
	m_playerIcon.Draw();
	m_miniMap.Draw();
}
