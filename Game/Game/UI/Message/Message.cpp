#include "Message.h"

void CMessage::Init(CVector2 windowSize, wchar_t* textureName)
{
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f,0.0f });
	m_window.SetSize(windowSize);
	m_window.SetAlpha(0.5f);

	wchar_t filePath[256];
	swprintf(filePath, L"Assets/sprite/%s.png", textureName);
	texture = TextureResource().LoadTexture(filePath);
	m_message.Init(texture);
	m_message.SetPosition({ 0.0f,0.0f });
	m_message.SetSize({ 400.0f, 200.0f });
}

void CMessage::Update()
{
}

void CMessage::AfterDraw()
{
	m_window.Draw();
	m_message.Draw();
}
