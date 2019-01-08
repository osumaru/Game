#include "Message.h"

void CMessage::Init(CVector2 size, wchar_t* string)
{
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize(size);

	m_font.Init(string);
	m_font.SetPosition({ 0.0f, 0.0f });
	m_font.SetSize({ 0.7f, 0.7f });
}

void CMessage::Update()
{
}

void CMessage::AfterDraw()
{
	m_window.Draw();
	m_font.Draw();
}
