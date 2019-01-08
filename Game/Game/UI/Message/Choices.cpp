#include "Choices.h"

void CChoices::Init(wchar_t* select1, wchar_t* select2)
{
	//選択肢の初期化
	m_yes.Init(select1);
	m_yes.SetPosition({ 0.0f, -150.0f});
	m_yes.SetSize({ 250.0f, 250.0f });
	m_no.Init(select2);
	m_no.SetPosition({ 0.0f, -250.0f});
	m_no.SetSize({ 250.0f, 250.0f });
	//スプライトの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/cursor.png");
	m_cursor.Init(texture);
	m_cursor.SetPosition({ -150.0f, -150.0f });
	m_cursor.SetSize({ 250.0f, 250.0f });
}

void CChoices::Update()
{
	//スティックを上に倒した、又は十字キーの上を押した
	if (Pad().GetLeftStickY() > 0.0f || Pad().IsTriggerButton(enButtonUp))
	{
		//状態を変更
		m_state = Yes;
		//カーソルの座標を変更
		m_cursor.SetPosition({ -150.0f, -150.0f });
	}
	//スティックを下に倒した、又は十字キーの下を押した
	else if (Pad().GetLeftStickY() < 0.0f || Pad().IsTriggerButton(enButtonDown))
	{
		//状態を変更
		m_state = No;
		//カーソルの座標を変更
		m_cursor.SetPosition({ -100.0f, -250.0f });
	}
}

void CChoices::AfterDraw()
{
	m_yes.Draw();
	m_no.Draw();
	m_cursor.Draw();
}
