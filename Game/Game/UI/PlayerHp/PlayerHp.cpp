#include "stdafx.h"
#include "PlayerHp.h"
#include "../../Player/Player.h"

void CPlayerHp::Init()
{


	//�v���C���[��Health��Hp��x�����̃T�C�Y�ɐݒ�
	m_playerHp = GetPlayer().GetStatus().Health;
	m_playerMaxHp = (float)GetPlayer().GetStatus().Health;

	//�v���C���[HP�̃��[�h
	m_playerHpTexture = TextureResource().LoadTexture(L"Assets/sprite/hp2.png");
	m_playerHpSprite.Init(m_playerHpTexture);
	m_playerHpSprite.SetCenterPosition({ m_playerHpCenterPos });
	m_playerHpSprite.SetPosition({ m_playerHpPos });
	m_playerHpSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
	m_playerHpSprite.SetSize({ m_playerHpSize.x, m_playerHpSize.y});
	
	//�v���C���[HP�o�b�N�O���E���h�̃��[�h
	m_playerHpBackTexture = TextureResource().LoadTexture(L"Assets/sprite/hpBack.png");
	m_playerHpBackSprite.Init(m_playerHpBackTexture);
	m_playerHpBackSprite.SetCenterPosition({ m_playerHpBackCenterPos });
	m_playerHpBackSprite.SetPosition({ m_playerHpBackPos });
	m_playerHpBackSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
	m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x,m_playerHpBackSize.y });

	//�v���C��HP�̃t���[���̃��[�h
	m_playerHpFrameTexture = TextureResource().LoadTexture(L"Assets/sprite/PlayerHPFrame.png");
	m_playerHpFrameSprite.Init(m_playerHpFrameTexture);
	m_playerHpFrameSprite.SetCenterPosition({ m_playerHpFrameCenterPos });
	m_playerHpFrameSprite.SetPosition({ m_playerHpFramePos });
	m_playerHpFrameSize.x = m_playerMaxHpSizeX + 8.0f;
	m_playerHpFrameSprite.SetSize({ m_playerHpFrameSize.x,m_playerHpFrameSize.y });

}

void CPlayerHp::Update()
{
	//�ő�HP���ω�������v���C���[�X�e�[�^�X����擾����
	if (m_playerMaxHp != GetPlayer().GetStatus().MaxHealth)
	{
		m_playerMaxHp = (float)GetPlayer().GetStatus().MaxHealth;
	}

	//�v���C���[��Hp���ω������Ƃ��Ƀ����o�ϐ��Ƀv���C���[Hp��������
	if (m_playerHp != GetPlayer().GetStatus().Health)
	{
		//Hp���������Ƃ��ɔw�i�̃T�C�Y�����₷
		if (m_playerHp < GetPlayer().GetStatus().Health)
		{
			m_playerHpBackSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
			m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x, m_playerHpSize.y });
		}

		m_playerHpSize.x = (float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp));
		m_playerHpSprite.SetSize({ m_playerHpSize.x, m_playerHpSize.y });
		m_hpSubtractSpeed = max(0.0f, (float)(m_playerHp - GetPlayer().GetStatus().Health) / m_playerMaxHp * 10.0f);
		//�v���C���[Hp�X�V
		m_playerHp = GetPlayer().GetStatus().Health;
		m_delayTime = 0.0f;
	}

	//HP�̔w�i�����炵�Ă�������
	if ((float)(m_playerMaxHpSizeX*(GetPlayer().GetStatus().Health / m_playerMaxHp)) <= m_playerHpBackSize.x)
	{
		const float DELAY_TIME = 0.3f;
		if (m_delayTime < DELAY_TIME)
		{
			m_delayTime += GameTime().GetDeltaFrameTime();
		}
		else
		{
			m_playerHpBackSize.x -= m_hpSubtractSpeed;
			m_playerHpBackSprite.SetSize({ m_playerHpBackSize.x,m_playerHpBackSize.y });
		}
	}
}

void CPlayerHp::PostAfterDraw()
{
	m_playerHpFrameSprite.Draw();
	m_playerHpBackSprite.Draw();
	m_playerHpSprite.Draw();
}
