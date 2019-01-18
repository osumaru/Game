#include "stdafx.h"
#include "LoadScene.h"


CLoadScene::CLoadScene()
{
}


CLoadScene::~CLoadScene()
{
}

bool CLoadScene::Start()
{
	for (auto& fonts : m_font)
	{
		swprintf(m_text, L"0");
		fonts.Init(m_text);
		fonts.SetColor({ 1.0f,1.0f,1.0f,1.0f });
		fonts.SetSize({ 1.5f,1.5f });
		
	}
	m_font[0].SetPosition(m_fontNamePosition);
	m_font[1].SetPosition(m_fontTextPosition);

	m_loadTexture[0] = TextureResource().LoadTexture(L"Assets/sprite/Back_Texture.png");
	m_LoadSprite[0].Init(m_loadTexture[0]);
	m_LoadSprite[0].SetSize({ 950.0f,600.0f });

	m_loadTexture[1] = TextureResource().LoadTexture(L"Assets/sprite/Logo/Logo1.png");
	m_LoadSprite[1].Init(m_loadTexture[1]);
	m_LoadSprite[1].SetSize({ 100.0f,100.0f });
	m_LoadSprite[1].SetPosition({ 550.0f,-300.0f });
	m_equipItem.Start();
	m_isTextChange = true;
	return true;
}

void CLoadScene::Update()
{
	
	m_alphaTime += GameTime().GetDeltaFrameTime();
	if (m_isAlphaDown) { m_alpha -= GameTime().GetDeltaFrameTime() / CHANGE_TIME; }
	else { m_alpha += GameTime().GetDeltaFrameTime() / CHANGE_TIME; }
	if (m_alphaTime > CHANGE_TIME)
	{
		m_isTextChange = true;
		m_alphaTime = 0.0f;
		if (m_isAlphaDown)
		{
			m_isAlphaDown = false;
			m_alpha = 0.0f;
		}
		else
		{
			m_isAlphaDown = true;
			m_alpha = 1.0f;
		}
	}

	if (m_isTextChange)
	{
		//ñ≥å¿ÉãÅ[ÉvÇµÇΩÇÁÇ≤ÇﬂÇÒÇÀ
		while(m_number == Random().GetRandInt() % 10 + 1);
		{

		}
		m_number = Random().GetRandInt() % 10 + 1;
		swprintf(m_text, m_equipItem.GetItemStatus_ItemId(m_number).ItemName);
		m_font[0].Init(m_text);
		
		swprintf(m_text, m_equipItem.GetItemStatus_ItemId(m_number).ItemText);
		m_font[1].Init(m_text);
		
		m_isTextChange = false;
	}
	m_LoadSprite[1].SetAlpha(m_alpha);
	for (auto& fonts : m_font)
	{
		fonts.SetColor(m_fontCol);
	}
}

void CLoadScene::AfterDraw()
{
	if (!m_isDraw) { return; }
	Sleep(50);
	Update();
	for (auto& Sprites : m_LoadSprite)
	{
		Sprites.Draw();
	}
	for (auto& fonts : m_font)
	{
		fonts.Draw();
	}
}
