#include "stdafx.h"
#include "PlayerHp.h"


void CPlayerHp::Init()
{
	//�v���C���[HP�̃��[�h
	m_playerHpTexture.Load(L"Assets/sprite/hp2.png");
	m_playerHpSprite.Init(&m_playerHpTexture);
	m_playerHpSprite.SetCenterPosition({ m_playerHpCenterPos });
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSprite.SetSize({ m_playerHpSize });
	
	//�v���C���[HP�o�b�N�O���E���h�̃��[�h
	m_playerHpBackTexture.Load(L"Assets/sprite/hpBack.png");
	m_playerHpBackSprite.Init(&m_playerHpBackTexture);
	m_playerHpBackSprite.SetCenterPosition({ m_playerHpBackCenterPos });
	m_playerHpBackSprite.SetPosition({ m_playerHpBackPos });
	m_playerHpBackSprite.SetSize({ m_playerHpBackSize });

	//PlayerDamage(80.0f);
}

void CPlayerHp::Update()
{
	//HP�̔w�i�����炵�Ă�������
	if (m_playerHpSize.x >= m_playerHpBackSize.x) { return; }
	m_playerHpBackSize.x -= m_hpSubtractSpeed;
	m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x, m_playerHpBackSize.y });
}

void CPlayerHp::PlayerDamage(float DamageValue)
{
	m_playerHpSize.x -= DamageValue;
	m_playerHpSprite.SetSize({ m_playerHpSize.x,m_playerHpSize.y });
}

void CPlayerHp::Draw()
{
	m_playerHpBackSprite.Draw();
	m_playerHpSprite.Draw();
}
