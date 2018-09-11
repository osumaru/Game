#include "stdafx.h"
#include "DamageNumber.h"
#include "../../Player/Player.h"
#include "../../Enemy/IEnemy.h"

void CDamegeNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 30.0f,50.0f };

	//数字のスプライトを初期化
	for (int i = 0; i < 3; i++) {
		m_number[i] = New<CNumber>(0);
		m_numPos.x = m_numSize.x * i;
		m_number[i]->Init(m_numPos, m_numSize);
		m_number[i]->SetIsActive(false);
	}
}

void CDamegeNumber::DamageCalculation()
{
	//プレイヤーの攻撃力を取得
	int playerStrength = GetPlayer().GetStatus().Strength;
	playerStrength %= 1000;
	if (playerStrength / 100 > 0) {
		m_number[0]->SetIsActive(true);
		m_number[0]->SetNumber(playerStrength / 100);
	}
	else {
		m_number[0]->SetIsActive(false);
	}
	playerStrength %= 100;
	if (playerStrength / 10 > 0) {
		m_number[1]->SetIsActive(true);
		m_number[1]->SetNumber(playerStrength / 10);
	}
	else {
		if (m_number[0]->IsActive() == true) {
			m_number[1]->SetNumber(0);
			m_number[1]->SetIsActive(true);
		}
		else {
			m_number[1]->SetIsActive(false);
		}
	}
	playerStrength %= 10;
	m_number[2]->SetIsActive(true);
	m_number[2]->SetNumber(playerStrength);
}

void CDamegeNumber::Reset()
{
	m_number[0]->SetIsActive(false);
	m_number[1]->SetIsActive(false);
	m_number[2]->SetIsActive(false);
}
