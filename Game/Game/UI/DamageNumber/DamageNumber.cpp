#include "stdafx.h"
#include "DamageNumber.h"
#include "Number.h"

void CDamegeNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 30.0f,50.0f };

	//数字のスプライトを初期化
	for (int i = 0; i < EnDigit::enDigit_Num; i++) {
		m_number[i] = New<CNumber>(0);
		m_numPos.x = m_numSize.x * i;
		m_number[i]->Init(m_numPos, m_numSize);
		m_number[i]->SetIsActive(false);
	}
}

void CDamegeNumber::DamageCalculation(int dmg)
{
	//受けたダメージを取得
	int damage = dmg;
	damage %= 1000;
	if (damage / 100 > 0) {
		//百の位を表示
		m_number[EnDigit::enDigit_Hundred]->SetIsActive(true);
		m_number[EnDigit::enDigit_Hundred]->SetNumber(damage / 100);
	}
	else {
		m_number[EnDigit::enDigit_Hundred]->SetIsActive(false);
	}
	damage %= 100;
	if (damage / 10 > 0) {
		//十の位を表示
		m_number[EnDigit::enDigit_Ten]->SetIsActive(true);
		m_number[EnDigit::enDigit_Ten]->SetNumber(damage / 10);
	}
	else {
		//百の位も０の場合は十の位は表示しない
		if (m_number[EnDigit::enDigit_Hundred]->IsActive() == true) {
			m_number[EnDigit::enDigit_Ten]->SetNumber(0);
			m_number[EnDigit::enDigit_Ten]->SetIsActive(true);
		}
		else {
			m_number[EnDigit::enDigit_Ten]->SetIsActive(false);
		}
	}
	damage %= 10;
	//一の位を表示
	m_number[EnDigit::enDigit_One]->SetIsActive(true);
	m_number[EnDigit::enDigit_One]->SetNumber(damage);
}

void CDamegeNumber::Reset()
{
	//全ての位の表示をやめる
	m_number[EnDigit::enDigit_Hundred]->SetIsActive(false);
	m_number[EnDigit::enDigit_Ten]->SetIsActive(false);
	m_number[EnDigit::enDigit_One]->SetIsActive(false);
}
