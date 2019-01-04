#include "Retry.h"

void CRetry::Init()
{
	//スプライトの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/Continue.png");
	m_continue.Init(texture);
	m_continue.SetPosition({ 0.0f, -150.0f});
	m_continue.SetSize({ 250.0f, 250.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/Quit.png");
	m_quit.Init(texture);
	m_quit.SetPosition({ 0.0f, -250.0f});
	m_quit.SetSize({ 250.0f, 250.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition({ -150.0f, -150.0f });
	m_cursor.SetSize({ 250.0f, 250.0f });
}

void CRetry::Update()
{
	//スティックを上に倒した、又は十字キーの上を押した
	if (Pad().GetLeftStickY() > 0.0f || Pad().IsTriggerButton(enButtonUp))
	{
		//状態を変更
		m_state = Continue;
		//カーソルの座標を変更
		m_cursor.SetPosition({ -150.0f, -150.0f });
	}
	//スティックを下に倒した、又は十字キーの下を押した
	else if (Pad().GetLeftStickY() < 0.0f || Pad().IsTriggerButton(enButtonDown))
	{
		//状態を変更
		m_state = Quit;
		//カーソルの座標を変更
		m_cursor.SetPosition({ -100.0f, -250.0f });
	}
}

void CRetry::AfterDraw()
{
	m_continue.Draw();
	m_quit.Draw();
	m_cursor.Draw();
}
