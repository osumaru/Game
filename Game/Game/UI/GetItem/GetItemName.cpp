#include "GetItemName.h"
#include "../../Scene/SceneManager.h"
#include "../Menu/Menu.h"

void CGetItemName::Init(CTexture* texture, wchar_t* itemName)
{
	CTexture * backTex = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_sprite[0].Init(backTex);
	m_sprite[0].SetSize({ 600.0f,100.0f });
	m_sprite[0].SetPosition({ 0.0f,-250.0f });

	m_sprite[1].Init(texture);
	m_sprite[1].SetSize({ 80,80.0f });
	m_sprite[1].SetPosition({ -200.0f,-250.0f });

	m_font.Init(itemName);
	m_font.SetPosition({ -150.0f,-230.0f });
	m_font.SetColor(CVector4::White);
}

void CGetItemName::Update()
{
	m_drawTime += GameTime().GetDeltaFrameTime();
	if (m_drawTime > 1.5f)
	{
		m_drawTime = 0.0f;
		Delete(this);
		return;
	}
}

void CGetItemName::PostAfterDraw()
{
	if (GetSceneManager().GetMenu()->GetIsDraw())
	{
		return;
	}

	m_sprite[0].Draw();
	m_sprite[1].Draw();
	m_font.Draw();
}
