#include "ArrowRemain.h"
#include "../../Player/Player.h"
#include "../../Player/Weapon/Bow.h"

void CArrowRemain::Init()
{
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/ArrowSynbol.png");
	CVector2 pos = { -600.0f, 220.0f };
	m_arrowSynbol.Init(texture);
	m_arrowSynbol.SetSize({ 60.0f, 60.0f });
	m_arrowSynbol.SetPosition(pos);
	pos.x = -500.0f;
	for (int i = 0; i < DECIMAL_NUM; i++)
	{
		wchar_t filePath[128];
		swprintf(filePath, L"Assets/sprite/ArrowRemainNum/%d.png", i);
		m_pNumTexture[i] = TextureResource().LoadTexture(filePath);
	}
	for (int i = 0; i < DIGIT_NUM; i++)
	{
		m_remainNum[i].Init(m_pNumTexture[0]);
		m_remainNum[i].SetSize({ 40.0f, 60.0f });
		m_remainNum[i].SetPosition(pos);
		pos.x -= 40.0f;
	}
}

void CArrowRemain::Update()
{
	int remainNum = dynamic_cast<CBow*>(GetPlayer().GetWeaponManager().GetWeapon(enWeaponArrow))->GetRemainNum();
	int textureNum[DIGIT_NUM];
	for (int i = 0; i < DIGIT_NUM; i++)
	{
		textureNum[i] = remainNum % DECIMAL_NUM;
		remainNum /= DECIMAL_NUM;
	}
	for (int i = 0; i < DIGIT_NUM; i++)
	{
		CTexture* texture = m_pNumTexture[textureNum[i]];
		m_remainNum[i].SetTexture(texture);
		bool isDraw = false;
		//一桁目以外は余計な0を表示しない
		if (i != 0)
		{
			for (int j = DIGIT_NUM - 1; i <= j; j--)
			{
				if (textureNum[j] != 0)
				{
					isDraw = true;
					break;
				}
			}
		}
		else
		{
			isDraw = true;
		}
		m_remainNum[i].SetIsDraw(isDraw);
	}
}

void CArrowRemain::PostAfterDraw()
{
	m_arrowSynbol.Draw();
	for (int i = 0; i < DIGIT_NUM; i++)
	{
		m_remainNum[i].Draw();
	}
}