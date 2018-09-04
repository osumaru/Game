#include "stdafx.h"
#include "PlayerHp.h"


void CPlayerHp::Init()
{
	//プレイヤーHPのロード
	m_playerHpTexture.Load(L"Assets/sprite/hp1.png");
	m_playerHpSprite.Init(&m_playerHpTexture);
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSprite.SetSize({ m_playerHpSize });
}

void CPlayerHp::Update()
{

}

void CPlayerHp::PlayerDamage(float DamageValue)
{
	m_playerHpSprite.SetSize({ DamageValue,m_playerHpSize.y });
}

void CPlayerHp::Draw()
{
	m_playerHpSprite.Draw();
}
