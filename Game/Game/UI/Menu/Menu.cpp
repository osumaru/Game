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

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_numberTexture[i][j] = new CTexture;
			m_number[i][j] = new CSprite;
			m_numberTexture[i][j] = TextureResource().LoadTexture(L"Assets/sprite/number/number0.png");
			m_number[i][j]->Init(m_numberTexture[i][j]);
			m_number[i][j]->SetPosition({ m_numberPos});
			m_number[i][j]->SetSize({ 65.0f,65.0f });
			m_numberPos.x += 30.0;
		}
		if(i==4)
		{ 
			m_numberPos.y -= 43.0f;
		}
		m_numberPos.x = 500.0f;
		m_numberPos.y -= 57.0f;
	}
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


	m_PlayerStatus = GetPlayer().GetStatus();

	if (Pad().IsTriggerButton(enButtonSelect))
	{

		StatusMath();
	}
}

//メニュー画面に表示されるプレイヤーのステータスの数値を決める処理
void CMenu::StatusMath()
{


	for (int i = 0; i < 7; i++)
	{
		
			int num = 1111 * i;
			wchar_t filePath[256];
			swprintf(filePath, L"Assets/sprite/number/number%d.png", num / 1000);
			m_numberTexture[i][0] = m_numberTexture[i][0] = TextureResource().LoadTexture(filePath);
			m_number[i][0]->Init(m_numberTexture[i][0]);
			m_number[i][0]->SetSize({ 65.0f,65.0f });
			num %= 1000;
			/*swprintf(filePath, L"Assets/sprite/number/number%d.png", num / 100);
			m_numberTexture[i][1] = m_numberTexture[i][1] = TextureResource().LoadTexture(filePath);
			m_number[i][1]->Init(m_numberTexture[i][1]);
			m_number[i][1]->SetSize({ 65.0f,65.0f });
			num %= 100;

			swprintf(filePath, L"Assets/sprite/number/number%d.png", num / 10);
			m_numberTexture[i][2] = m_numberTexture[i][2] = TextureResource().LoadTexture(filePath);
			m_number[i][2]->Init(m_numberTexture[i][2]);
			m_number[i][2]->SetSize({ 65.0f,65.0f });
			num %= 10;

			swprintf(filePath, L"Assets/sprite/number/number%d.png", num );
			m_numberTexture[i][3] = m_numberTexture[i][3] = TextureResource().LoadTexture(filePath);
			m_numberTexture[i][3]->Load(filePath);
			m_number[i][3]->Init(m_numberTexture[i][3]);
			m_number[i][3]->SetSize({ 65.0f,65.0f });*/


	
	}


}

//メニュー画面の描画処理
void CMenu::Draw()
{
	if (m_Draw)
	{
		m_menu.Draw();
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 4; j++)
			{

				m_number[i][j]->Draw();
			}
		}


		

	}

}