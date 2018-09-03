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
	m_menu.SetPosition({ 0.0f, 0.0f });
	m_menu.SetSize({ 1280.0f,720.0f });


}


void CMenu::Update()
{
	if (GetPad().IsTriggerButton(enButtonSelect))
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

		m_menu.Draw();

	}

}