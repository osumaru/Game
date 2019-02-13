#include "GetItem.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"

void CGetItem::Init()
{
	//スプライトの初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonA.png");
	m_aButton.Init(texture);
	m_aButton.SetPosition({ -25.0f, -250.0f });
	m_aButton.SetSize({ 30.0f, 30.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/back.png");
	m_back.Init(texture);
	m_back.SetPosition({ 0.0f, -250.0f });
	m_back.SetSize({ 90.0f, 35.0f });
	m_back.SetAlpha(0.8f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/pickUp.png");
	m_pickUp.Init(texture);
	m_pickUp.SetPosition({ 25.0f, -250.0f });
	m_pickUp.SetSize({ 60.0f, 60.0f });
	m_itemName.Init();
}

void CGetItem::Update()
{
	if (m_drawCount < 0 || GetPlayer().GetIsDied())
	{
		m_drawCount = 0;
	}
	m_itemName.Update();
}

void CGetItem::PostAfterDraw()
{
	if (m_drawCount > 0)
	{
		m_back.Draw();
		m_aButton.Draw();
		m_pickUp.Draw();
	}
	m_itemName.PostAfterDraw();
}
