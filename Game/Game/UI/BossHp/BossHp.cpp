#include "stdafx.h"
#include "BossHp.h"
#include "../../Enemy/Maw.h"


void CBossHp::Init()
{
	//Health��Hp��x�����̃T�C�Y�ɐݒ�
	m_bossHp = GetMaw().GetSmawStatus().Hp;
	m_bossMaxHp = (float)GetMaw().GetSmawStatus().Hp;

	//HP�̃��[�h
	m_bossHpTexture.Load(L"Assets/sprite/hp2.png");
	m_bossHpSprite.Init(&m_bossHpTexture);
	m_bossHpSprite.SetCenterPosition({ m_bossHpCenterPos });
	m_bossHpSprite.SetPosition({ m_bossHpPos });
	m_bossHpSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
	m_bossHpSprite.SetSize({ m_bossHpSize.x, m_bossHpSize.y });

	//HP�o�b�N�O���E���h�̃��[�h
	m_bossHpBackTexture.Load(L"Assets/sprite/hpBack.png");
	m_bossHpBackSprite.Init(&m_bossHpBackTexture);
	m_bossHpBackSprite.SetCenterPosition({ m_bossHpBackCenterPos });
	m_bossHpBackSprite.SetPosition({ m_bossHpBackPos });
	m_bossHpBackSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
	m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x,m_bossHpBackSize.y });

	//this->SetIsActive(false);
}

void CBossHp::Update()
{
	//if (GetMaw().) { return; }
	//�ő�HP���ω�������X�e�[�^�X����擾����
	if (m_bossMaxHp != GetMaw().GetSmawStatus().MaxHp)
	{
		m_bossMaxHp = (float)GetMaw().GetSmawStatus().MaxHp;
	}

	//Hp���ω������Ƃ��Ƀ����o�ϐ��Ƀv���C���[Hp��������
	if (m_bossHp != GetMaw().GetSmawStatus().Hp)
	{
		//Hp���������Ƃ��ɔw�i�̃T�C�Y�����₷
		if (m_bossHp < GetMaw().GetSmawStatus().Hp)
		{
			m_bossHpBackSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
			m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x, m_bossHpSize.y });
		}

		m_bossHpSize.x = (float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp));
		m_bossHpSprite.SetSize({ m_bossHpSize.x, m_bossHpSize.y });

		//Hp�X�V
		m_bossHp = GetMaw().GetSmawStatus().Hp;
	}

	//HP�̔w�i�����炵�Ă�������
	if ((float)(m_bossMaxHpSizeX*(GetMaw().GetSmawStatus().Hp / m_bossMaxHp)) <= m_bossHpBackSize.x)
	{
		m_bossHpBackSize.x -= m_hpSubtractSpeed;
		m_bossHpBackSprite.SetSize({ m_bossHpBackSize.x,m_bossHpBackSize.y });
	}
}

void CBossHp::AfterDraw()
{
	m_bossHpBackSprite.Draw();
	m_bossHpSprite.Draw();
}