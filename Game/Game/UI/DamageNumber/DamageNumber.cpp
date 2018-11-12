#include "stdafx.h"
#include "DamageNumber.h"

void CDamageNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 15.0f,25.0f };

	//数字のスプライトを初期化
	for (int i = 0; i < EnDigit::enDigit_Num; i++) {
		m_numPos.x -= m_numSize.x * i;
		m_number[i].Init(m_numPos, m_numSize);
	}
}

void CDamageNumber::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_timer > m_drawTime) {
		//描画する時間より長くなったら段々透明にしていく
		m_alphaTime += GameTime().GetDeltaFrameTime();
		float alpha = 1.0f - m_alphaTime;
		if (alpha < 0.0f)
		{
			//透明になった
			SetIsActive(false);
			return;
		}
		for (int i = 0; i < EnDigit::enDigit_Num; i++)
		{
			m_number[i].SetAlpha(alpha);
		}
	}
}

void CDamageNumber::AfterDraw()
{
	for (int i = 0; i < EnDigit::enDigit_Num; i++)
	{
		m_number[i].Draw();
	}
}

void CDamageNumber::DamageCalculation(int dmg)
{
	//受けたダメージを取得
	int damage = dmg;
	damage %= 1000;
	if (damage / 100 > 0) {
		//百の位を表示
		m_number[EnDigit::enDigit_Hundred].SetIsDraw(true);
		m_number[EnDigit::enDigit_Hundred].SetNumber(damage / 100);
	}
	else {
		m_number[EnDigit::enDigit_Hundred].SetIsDraw(false);
	}
	damage %= 100;
	if (damage / 10 > 0) {
		//十の位を表示
		m_number[EnDigit::enDigit_Ten].SetIsDraw(true);
		m_number[EnDigit::enDigit_Ten].SetNumber(damage / 10);
	}
	else {
		//百の位も０の場合は十の位は表示しない
		if (m_number[EnDigit::enDigit_Hundred].GetIsDraw()) {
			m_number[EnDigit::enDigit_Ten].SetNumber(0);
			m_number[EnDigit::enDigit_Ten].SetIsDraw(true);
		}
		else {
			m_number[EnDigit::enDigit_Ten].SetIsDraw(false);
		}
	}
	damage %= 10;
	//一の位を表示
	m_number[EnDigit::enDigit_One].SetIsDraw(true);
	m_number[EnDigit::enDigit_One].SetNumber(damage);
}

void CDamageNumber::SetPosition(const CVector2 & position)
{
	CVector2 pos = position;
	for (int i = 0; i < EnDigit::enDigit_Num; i++)
	{
		m_number[i].SetPosition(pos);
		pos.x -= m_numSize.x * (i + 1);
	}
}