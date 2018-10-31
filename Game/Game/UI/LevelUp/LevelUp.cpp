#include "stdafx.h"
#include "LevelUp.h"
#include "../../Player/Player.h"

//Result��youdied�Ǝ��������ɏo�����ق������������������m��Ȃ�

CLevelUp::CLevelUp()
{
}


CLevelUp::~CLevelUp()
{
}

void CLevelUp::Init()
{
	//�v���C���[HP�̃��[�h
	m_playerLevelUpTexture.Load(L"Assets/sprite/levelup.png");
	m_playerLevelUpSprite.Init(&m_playerLevelUpTexture);
	m_playerLevelUpSprite.SetPosition({ m_playerLevelUpPos });
	m_playerLevelUpSprite.SetSize({ m_playerLevelUpSize});
	m_playerLevelUpSprite.SetAlpha(0.0f);
	m_playerLevelValue = GetPlayer().GetStatus().Level;
}

void CLevelUp::Update()
{
	//���x�����ς������
	if (GetPlayer().GetStatus().Level != m_playerLevelValue)
	{
		m_playerLevelValue = GetPlayer().GetStatus().Level;
		m_playerLevelUpAlpha = 1.0f;
		m_playerLevelUpSprite.SetAlpha(m_playerLevelUpAlpha);
	}

	m_playerLevelUpAlpha -= 0.1f;//GameTime().GetDeltaFrameTime() / 5.0f;
	//m_playerLevelUpSprite.SetAlpha(m_playerLevelUpAlpha);

	
}

void CLevelUp::AfterDraw()
{
	if (m_playerLevelUpAlpha <= 0.0f)
	{
		return;
	}
	m_playerLevelUpSprite.Draw();
}
