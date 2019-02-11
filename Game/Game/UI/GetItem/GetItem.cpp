#include "GetItem.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"
#include "../Menu/Menu.h"

void CGetItem::Init()
{
	//スプライトの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonA.png");
	m_aButton.Init(texture);
	m_aButton.SetPosition({ -25.0f, -250.0f });
	m_aButton.SetSize({ 30.0f, 30.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/back.png");
	m_back.Init(texture);
	m_back.SetPosition({ 0.0f, -250.0f });
	m_back.SetSize({ 90.0f, 35.0f });
	m_back.SetAlpha(0.8f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/pickUp.png");
	m_pickUp.Init(texture);
	m_pickUp.SetPosition({ 25.0f, -250.0f });
	m_pickUp.SetSize({ 60.0f, 60.0f });

	CTexture * backTex = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_sprite[0].Init(backTex);
	m_sprite[0].SetSize({ 600.0f,100.0f });
	m_sprite[0].SetPosition({ 0.0f,-250.0f });

	m_font.Init(L"10000000");
	m_font.SetPosition({ -150.0f,-230.0f });
	m_font.SetColor(CVector4::White);
}

void CGetItem::Update()
{
	if (m_drawCount < 0 || GetPlayer().GetIsDied())
	{
		m_drawCount = 0;
	}
	
}

void CGetItem::PostAfterDraw()
{
	if (GetSceneManager().GetMenu()->GetIsDraw())
	{
		return;
	}

	if (m_drawCount > 0)
	{
		m_back.Draw();
		m_aButton.Draw();
		m_pickUp.Draw();
	}
	if (m_isDrawItemName)
	{
		m_sprite[0].Draw();
		m_sprite[1].Draw();
		m_font.Draw();
	}
}
