#include "stdafx.h"
#include "PlayerHp.h"


void PlayerHp::Init()
{
	//プレイヤーHPのロード
	m_playerHpTexture.Load(L"Assets/sprite/hp1.png");
	m_playerHpSprite.Init(&m_playerHpTexture);
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSprite.SetSize({ m_playerHpSize });
}

void PlayerHp::Update()
{
}

void PlayerHp::Draw()
{
	m_playerHpSprite.Draw();
}
