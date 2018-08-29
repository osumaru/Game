#include "stdafx.h"
#include "MiniMap.h"

void MiniMap::Init()
{
	m_miniMapTexture.Load(L"Assets/sprite/miniMap.png");
	m_miniMap.Init(&m_miniMapTexture);
	m_miniMap.SetPosition({ 540.0f, -260.0f });
	m_miniMap.SetSize({ 180.0f,180.0f });

	m_playerIconTexture.Load(L"Assets/sprite/player_Icon.png");
	m_playerIcon.Init(&m_playerIconTexture);
	m_playerIcon.SetPosition({ 540.0f, -260.0f });
	m_playerIcon.SetSize({ 50.0f,50.0f });
}

void MiniMap::Update()
{
}

void MiniMap::Draw()
{
	m_miniMap.Draw();
	m_playerIcon.Draw();
}
