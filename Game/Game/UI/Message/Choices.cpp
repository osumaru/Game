#include "Choices.h"

void CChoices::Init()
{
	//スプライトの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/yes.png");
	m_yes.Init(texture);
	m_yes.SetPosition({ -75.0f, -150.0f });
	m_yes.SetSize({ 160.0f, 50.0f });
	m_yes.SetAlpha(0.0f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/no.png");
	m_no.Init(texture);
	m_no.SetPosition({ 75.0f, -150.0f });
	m_no.SetSize({ 160.0f, 50.0f });
	m_no.SetAlpha(0.0f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition(m_no.GetPosition());
	m_cursor.SetSize({ 125.0f, 50.0f });
	m_cursor.SetAlpha(0.0f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/MessageWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f, -150.0f });
	m_window.SetSize({ 500.0f, 100.0f });
	m_window.SetAlpha(0.0f);
}

void CChoices::Update()
{
	//透明になっている
	if (m_isAlpha) 
	{
		m_timer += GameTime().GetDeltaFrameTime();
		if (m_timer >= 1.0f)
		{
			//不透明になった
			m_timer = 1.0f;
			m_isAlpha = false;
		}
		m_yes.SetAlpha(m_timer);
		m_no.SetAlpha(m_timer);
		m_cursor.SetAlpha(m_timer);
		m_window.SetAlpha(m_timer);
	}
	else 
	{
		//スティックを右に倒した、又は十字キーの右を押した
		if (Pad().GetLeftStickX() > 0.0f || Pad().IsTriggerButton(enButtonRight))
		{
			//状態を変更
			m_state = No;
			//カーソルの座標を変更
			m_cursor.SetPosition(m_no.GetPosition());
		}
		//スティックを左に倒した、又は十字キーの左を押した
		else if (Pad().GetLeftStickX() < 0.0f || Pad().IsTriggerButton(enButtonLeft))
		{
			//状態を変更
			m_state = Yes;
			//カーソルの座標を変更
			m_cursor.SetPosition(m_yes.GetPosition());
		}

		if (Pad().IsTriggerButton(enButtonA))
		{
			//選んだ
			m_isSelect = true;
		}
		else
		{
			m_isSelect = false;
		}
	}
}

void CChoices::PostAfterDraw()
{
	m_window.Draw();
	m_yes.Draw();
	m_no.Draw();
	m_cursor.Draw();
}
