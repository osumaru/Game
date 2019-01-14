#include "stdafx.h"
#include "Number.h"

void CNumber::Init(const CVector2& numPos, const CVector2& numSize)
{
	for (int i = 0; i < EnNumber::enNumber_Num; i++) {
		wchar_t filePath[256];
		swprintf(filePath, L"Assets/sprite/damageNumber/%d.png", i);
		m_numberTexture[i] = TextureResource().LoadTexture(filePath);
		m_number[i].Init(m_numberTexture[i]);
		m_number[i].SetPosition(numPos);
		m_number[i].SetSize(numSize);
	}
}

void CNumber::Draw()
{
	m_number[m_num].Draw();
}