#include "stdafx.h"
#include "DamageNumber.h"
#include "../../Player/Player.h"
#include "../../Enemy/Enemy.h"

void CDamegeNumber::Init()
{
	m_numPos = { 0.0f,0.0f };
	m_numSize = { 100.0f,150.0f };

	for (int i = 0; i < 3; i++) {
		m_number[i] = New<CNumber>(0);
		m_numPos.x = m_numSize.x * i;
		m_number[i]->Init(m_numPos, m_numSize);
		m_number[i]->SetIsActive(false);
	}
}


void CDamegeNumber::DamageCalculation(CPlayer* player, CEnemy* enemy)


{
	Vector3 toEnemy = enemy->GetPosition() - player->GetPosition();
	float length = toEnemy.Length();
	if (length < 30.0f) {
		if (GetPad().IsTriggerButton(enButtonA)){			
			int playerStrength = player->GetStatus().Strength;
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
	}
	else {
		m_number[0]->SetIsActive(false);
		m_number[1]->SetIsActive(false);
		m_number[2]->SetIsActive(false);
	}
}
