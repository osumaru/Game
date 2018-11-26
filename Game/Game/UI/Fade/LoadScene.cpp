#include "stdafx.h"
#include "LoadScene.h"


CLoadScene::CLoadScene()
{
}


CLoadScene::~CLoadScene()
{
}

bool CLoadScene::Start()
{
	swprintf(m_text, L"NOW_LOADING");
	m_font.Init(m_text);
	m_font.SetColor({ 1.0f,1.0f,1.0f,1.0f });
	m_font.SetSize({ 3.0f,3.0f });
	m_fontPosition.x -= 300.0f;
	m_font.SetPosition(m_fontPosition);
	return true;
}

void CLoadScene::Update()
{
	CVector4 col = CVector4::White;
	Sleep(100);
	col.x = CRandom::GetInstance().GetRandDouble();
	col.y = CRandom::GetInstance().GetRandDouble();
	col.z = CRandom::GetInstance().GetRandDouble();
	m_font.SetColor(col);
}

void CLoadScene::AfterDraw()
{
	if (!m_isDraw) { return; }
	Sleep(50);
	Update();
	m_font.Draw();
}
