#include "stdafx.h"
#include "DamageNumber.h"

void CDamageNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 15.0f,25.0f };

	//�����̃X�v���C�g��������
	for (int i = 0; i < EnDigit::enDigit_Num; i++) {
		m_numPos.x -= m_numSize.x * i;
		m_number[i].Init(m_numPos, m_numSize);
	}
}

void CDamageNumber::Update()
{
	m_timer += GameTime().GetDeltaFrameTime();

	if (m_timer > m_drawTime) {
		//�`�悷�鎞�Ԃ�蒷���Ȃ�����i�X�����ɂ��Ă���
		m_alphaTime += GameTime().GetDeltaFrameTime();
		float alpha = 1.0f - m_alphaTime;
		if (alpha < 0.0f)
		{
			//�����ɂȂ���
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
	//�󂯂��_���[�W���擾
	int damage = dmg;
	damage %= 1000;
	if (damage / 100 > 0) {
		//�S�̈ʂ�\��
		m_number[EnDigit::enDigit_Hundred].SetIsDraw(true);
		m_number[EnDigit::enDigit_Hundred].SetNumber(damage / 100);
	}
	else {
		m_number[EnDigit::enDigit_Hundred].SetIsDraw(false);
	}
	damage %= 100;
	if (damage / 10 > 0) {
		//�\�̈ʂ�\��
		m_number[EnDigit::enDigit_Ten].SetIsDraw(true);
		m_number[EnDigit::enDigit_Ten].SetNumber(damage / 10);
	}
	else {
		//�S�̈ʂ��O�̏ꍇ�͏\�̈ʂ͕\�����Ȃ�
		if (m_number[EnDigit::enDigit_Hundred].GetIsDraw()) {
			m_number[EnDigit::enDigit_Ten].SetNumber(0);
			m_number[EnDigit::enDigit_Ten].SetIsDraw(true);
		}
		else {
			m_number[EnDigit::enDigit_Ten].SetIsDraw(false);
		}
	}
	damage %= 10;
	//��̈ʂ�\��
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