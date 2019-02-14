#include "GetItemName.h"
#include "../../Scene/SceneManager.h"
#include "../Menu/Menu.h"

void CGetItemName::Init()
{
	CTexture * backTex = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_sprite[0].Init(backTex);
	m_sprite[0].SetSize({ 600.0f,100.0f });
	m_sprite[0].SetPosition({ 0.0f,-250.0f });

	m_sprite[1].Init(backTex);
	m_sprite[1].SetSize({ 80,80.0f });
	m_sprite[1].SetPosition({ -200.0f,-250.0f });

	m_font.Init(L"111");
	m_font.SetPosition({ -150.0f,-230.0f });
	m_font.SetColor(CVector4::White);
	m_drawTime = 0.0f;
}

void CGetItemName::Update()
{
	if (!m_isDraw) { return; }
	m_drawTime += GameTime().GetDeltaFrameTime();
	if (m_drawTime > 1.5f)
	{
		m_drawTime = 0.0f;
		m_isDraw = false;
		return;
	}
}

void CGetItemName::PostAfterDraw()
{
	if (GetSceneManager().GetMenu()->GetIsDraw())
	{
		return;
	}
	if (!m_isDraw) { return; }
	m_sprite[0].Draw();
	m_sprite[1].Draw();
	m_font.Draw();
}
void CGetItemName::SetIteName(CTexture* texture, wchar_t* itemName)
{
	m_sprite[1].SetTexture(texture);
	m_sprite[1].SetSize({ 80,80.0f });
	m_sprite[1].SetPosition({ -200.0f,-250.0f });
	m_font.SetString(itemName);
	m_isDraw = true;
	m_drawTime = 0.0f;
}
