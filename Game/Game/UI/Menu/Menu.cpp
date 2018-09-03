#include "stdafx.h"
#include "Menu.h"


CMenu::CMenu()
{
}


CMenu::~CMenu()
{
}


void CMenu::Init()
{
	m_Texture.Load(L"Assets/sprite/Menu.png");
	m_menu.Init(&m_Texture);
	m_menu.SetPosition({ -1.0f, -1.0f });
	m_menu.SetSize({ 1290.0f,720.0f });

	m_numberTexture.Load(L"Assets/sprite/number/number0.png");
	m_number.Init(&m_numberTexture);
	m_number.SetPosition({ 500.0f, 100.0f });
	m_number.SetSize({ 65.0f,65.0f });


}


void CMenu::Update()
{
	if (Pad().IsTriggerButton(enButtonSelect))
	{
		if (m_Draw)
		{
			m_Draw = false;
		}
		else
		{
			m_Draw = true;
		}
	}


}

void CMenu::Draw()
{
	if (m_Draw)
	{

		
		m_number.Draw();
		m_menu.Draw();

	}

}