#include "stdafx.h"
#include "DamageNumber.h"
#include "Number.h"

void CDamageNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 15.0f,25.0f };

	//�����̃X�v���C�g��������
	for (int i = 0; i < EnDigit::enDigit_Num; i++) {
		m_number[i] = New<CNumber>(0);
		m_numPos.x -= m_numSize.x * i;
		m_number[i]->Init(m_numPos, m_numSize);
		m_number[i]->SetIsActive(false);
	}
}

void CDamageNumber::DamageCalculation(int dmg)
{
	//�󂯂��_���[�W���擾
	int damage = dmg;
	damage %= 1000;
	if (damage / 100 > 0) {
		//�S�̈ʂ�\��
		m_number[EnDigit::enDigit_Hundred]->SetIsActive(true);
		m_number[EnDigit::enDigit_Hundred]->SetNumber(damage / 100);
	}
	else {
		m_number[EnDigit::enDigit_Hundred]->SetIsActive(false);
	}
	damage %= 100;
	if (damage / 10 > 0) {
		//�\�̈ʂ�\��
		m_number[EnDigit::enDigit_Ten]->SetIsActive(true);
		m_number[EnDigit::enDigit_Ten]->SetNumber(damage / 10);
	}
	else {
		//�S�̈ʂ��O�̏ꍇ�͏\�̈ʂ͕\�����Ȃ�
		if (m_number[EnDigit::enDigit_Hundred]->IsActive() == true) {
			m_number[EnDigit::enDigit_Ten]->SetNumber(0);
			m_number[EnDigit::enDigit_Ten]->SetIsActive(true);
		}
		else {
			m_number[EnDigit::enDigit_Ten]->SetIsActive(false);
		}
	}
	damage %= 10;
	//��̈ʂ�\��
	m_number[EnDigit::enDigit_One]->SetIsActive(true);
	m_number[EnDigit::enDigit_One]->SetNumber(damage);
}

void CDamageNumber::IndicateReset()
{
	m_number[EnDigit::enDigit_One]->SetIsActive(false);
	m_number[EnDigit::enDigit_Ten]->SetIsActive(false);
	m_number[EnDigit::enDigit_Hundred]->SetIsActive(false);
}

void CDamageNumber::SetPosition(const CVector2 & position)
{
	m_numPos = position;
	for (int i = 0; i < EnDigit::enDigit_Num; i++)
	{
		m_number[i]->SetPosition(m_numPos);
		m_numPos.x -= m_numSize.x * (i + 1);
	}
}

void CDamageNumber::Relese()
{
	for (int i = 0; i < EnDigit::enDigit_Num; i++) {
		Delete(m_number[i]);
	}
}
