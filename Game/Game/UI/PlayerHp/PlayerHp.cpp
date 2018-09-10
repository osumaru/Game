#include "stdafx.h"
#include "PlayerHp.h"
#include "../../Player/Player.h"

void CPlayerHp::Init()
{
	//�v���C���[��Health��Hp��x�����̃T�C�Y�ɐݒ�
	m_playerHp = (float)GetPlayer().GetStatus().Health;

	//�v���C���[HP�̃��[�h
	m_playerHpTexture.Load(L"Assets/sprite/hp2.png");
	m_playerHpSprite.Init(&m_playerHpTexture);
	m_playerHpSprite.SetCenterPosition({ m_playerHpCenterPos });
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSize.x = (float)m_playerHp;
	m_playerHpSprite.SetSize(m_playerHpSize);
	
	//�v���C���[HP�o�b�N�O���E���h�̃��[�h
	m_playerHpBackTexture.Load(L"Assets/sprite/hpBack.png");
	m_playerHpBackSprite.Init(&m_playerHpBackTexture);
	m_playerHpBackSprite.SetCenterPosition({ m_playerHpBackCenterPos });
	m_playerHpBackSprite.SetPosition({ m_playerHpBackPos });
	m_playerHpBackSize.x = (float)m_playerHp;
	m_playerHpBackSprite.SetSize(m_playerHpBackSize);

	//PlayerDamage(80.0f);
}

void CPlayerHp::Update()
{
	//�v���C���[��Hp���ω������Ƃ��Ƀ����o�ϐ��Ƀv���C���[Hp��������
	if (m_playerHp != GetPlayer().GetStatus().Health)
	{
		m_playerHpSize.x = (float)m_playerHp;
		m_playerHpSprite.SetSize(m_playerHpSize);
		//�v���C���[Hp�X�V
		m_playerHp = GetPlayer().GetStatus().Health;
	}
	//HP�̔w�i�����炵�Ă�������
	if (m_playerHpSize.x >= m_playerHpBackSize.x) { return; }
	m_playerHpBackSize.x -= m_hpSubtractSpeed;
	m_playerHpBackSprite.SetSize(m_playerHpBackSize);
}

//void CPlayerHp::PlayerDamage(float DamageValue)
//{
//	m_playerHpSize.x -= DamageValue;
//	m_playerHpSprite.SetSize(m_playerHpSize);
//}

void CPlayerHp::Draw()
{
	m_playerHpBackSprite.Draw();
	m_playerHpSprite.Draw();
}
