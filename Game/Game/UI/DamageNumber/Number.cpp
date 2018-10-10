#include "stdafx.h"
#include "../DamageNumber/Number.h"

void CNumber::Init(CVector2 numPos, CVector2 numSize)
{
	for (int i = 0; i < EnNumber::enNumber_Num; i++) {
		wchar_t filePath[256];
		swprintf(filePath, L"Assets/sprite/damageNumber/%d.png", i);
		m_numberTexture[i].Load(filePath);
		m_number[i].Init(&m_numberTexture[i]);
		m_number[i].SetPosition(numPos);
		m_number[i].SetSize(numSize);
	}
}

void CNumber::Update()
{
}

void CNumber::AfterDraw()
{
	m_number[m_num].Draw();
}

void CNumber::SetNumber(int num)
{
	m_num = num;
}
