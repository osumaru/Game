#include "stdafx.h"
#include "DamageNumber.h"

void DamegeNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 100.0f,150.0f };

	for (int i = 0; i < 3; i++) {
		m_number[i] = New<Number>(0);		
	}
	m_number[0]->Init(m_numPos, m_numSize);
	m_number[1]->Init({ 100.0f, 0.0f }, m_numSize);
	m_number[2]->Init({ 200.0f, 0.0f }, m_numSize);
}

void DamegeNumber::Update()
{
	if (GetPad().IsTriggerButton(EnPadButton::enButtonA)) {
		int randomNumber = GetRandom().GetRandSInt();
		randomNumber %= 1000;
		m_number[0]->SetNumber(randomNumber / 100);
		randomNumber %= 100;
		m_number[1]->SetNumber(randomNumber / 10);
		randomNumber %= 10;
		m_number[2]->SetNumber(randomNumber);
	}
}

void DamegeNumber::Draw()
{
}
