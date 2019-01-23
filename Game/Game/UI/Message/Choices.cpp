#include "Choices.h"

void CChoices::Init(wchar_t* select1, wchar_t* select2)
{
	//選択肢の初期化
	m_yes.Init(select1);
	m_yes.SetPosition({ -50.0f, -190.0f});
	m_yes.SetSize({ 0.7f,0.7f });
	m_no.Init(select2);
	m_no.SetPosition({ -50.0f, -290.0f});
	m_no.SetSize({ 0.7f,0.7f });
	//スプライトの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition({ -75.0f, -210.0f });
	m_cursor.SetSize({ 250.0f, 250.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_window.Init(texture);
	m_window.SetPosition({ 0.0f, -250.0f });
	m_window.SetSize({ 300.0f, 200.0f });
	m_window.SetAlpha(0.7f);
}

void CChoices::Update()
{
	//スティックを上に倒した、又は十字キーの上を押した
	if (Pad().GetLeftStickY() > 0.0f || Pad().IsTriggerButton(enButtonUp))
	{
		//状態を変更
		m_state = Yes;
		//カーソルの座標を変更
		m_cursor.SetPosition({ -75.0f, -210.0f });
	}
	//スティックを下に倒した、又は十字キーの下を押した
	else if (Pad().GetLeftStickY() < 0.0f || Pad().IsTriggerButton(enButtonDown))
	{
		//状態を変更
		m_state = No;
		//カーソルの座標を変更
		m_cursor.SetPosition({ -75.0f, -310.0f });
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

void CChoices::PostAfterDraw()
{
	m_window.Draw();
	m_cursor.Draw();
	m_yes.Draw();
	m_no.Draw();
}
