#include "stdafx.h"
#include "WeaponSelect.h"

void WeaponSelect::Init()
{
	m_crossKeyTexture.Load(L"Assets/sprite/crossKey.png");
	m_crossKey.Init(&m_crossKeyTexture);
	m_crossKey.SetPosition({ -520.0f, -240.0f });
	m_crossKey.SetSize({ 80.0f,80.0f });

	m_largeSwordTexture.Load(L"Assets/sprite/largeSword.png");
	m_largeSword.Init(&m_largeSwordTexture);
	m_largeSword.SetPosition({ -520.0f, -160.0f });
	m_largeSword.SetSize({ 60.0f,60.0f });

	m_swordTexture.Load(L"Assets/sprite/sword.png");
	m_sword.Init(&m_swordTexture);
	m_sword.SetPosition({ -440.0f,-240.0f });
	m_sword.SetSize({ 60.0f,60.0f });

	m_twinSwordTexture.Load(L"Assets/sprite/twinSword.png");
	m_twinSword.Init(&m_twinSwordTexture);
	m_twinSword.SetPosition({ -600.0f,-240.0f });
	m_twinSword.SetSize({ 60.0f,60.0f });

	m_bowTexture.Load(L"Assets/sprite/bow.png");
	m_bow.Init(&m_bowTexture);
	m_bow.SetPosition({ -520.0f, -320.0f });
	m_bow.SetSize({ 60.0f,60.0f });
}

void WeaponSelect::Update()
{
}

void WeaponSelect::Draw()
{
	m_crossKey.Draw();
	m_largeSword.Draw();
	m_sword.Draw();
	m_twinSword.Draw();
	m_bow.Draw();
}
