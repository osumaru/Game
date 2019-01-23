#include "stdafx.h"
#include "DamageNumber.h"
#include "../../Enemy/IEnemy.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Weapon/WeaponManager.h"

void CDamageNumber::Init(IEnemy* enemy)
{
	CVector2 numPos = { 0.0f,0.0f };
	CVector2 numSize = { 15.0f,25.0f };

	//数字のスプライトを初期化
	for (int i = 0; i < EnDigit::enDigit_Num; i++) {
		numPos.x -= numSize.x * i;
		m_number[i].Init(numPos, numSize);
	}

	m_enemy = enemy;

	//ダメージ計算
	DamageCalculation();
}

bool CDamageNumber::Start()
{
	CMatrix leftShoulderMatrix = m_enemy->GetBoneWorldMatrix(L"LeftShoulder");
	m_damagePos.x = leftShoulderMatrix.m[3][0];
	m_damagePos.y = leftShoulderMatrix.m[3][1];
	m_damagePos.z = leftShoulderMatrix.m[3][2];

	return true;
}

void CDamageNumber::Update()
{
	CMatrix viewMatrix = GetGameCamera().GetViewMatrix();
	CMatrix projectionMatrix = GetGameCamera().GetProjectionMatrix();
	//ビュー変換
	CVector4 viewPosition = m_damagePos;
	viewMatrix.Mul(viewPosition);
	//プロジェクション変換
	CVector4 projectionPosition = viewPosition;
	projectionMatrix.Mul(projectionPosition);
	projectionPosition = projectionPosition / projectionPosition.w;
	//スクリーン変換
	CVector2 screenPosition;
	screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * FrameBufferWidth() - (FrameBufferWidth() / 2.0f);
	screenPosition.y = (1.0f + projectionPosition.y) / 2.0f * FrameBufferHeight() - (FrameBufferHeight() / 2.0f);
	for (int i = 0; i < EnDigit::enDigit_Num; i++)
	{
		m_number[i].SetPosition(screenPosition);
		screenPosition.x = m_number[0].GetPosition().x - m_number[i].GetSize().x * (i + 1);
	}

	m_timer += GameTime().GetDeltaFrameTime();

	if (m_timer > m_drawTime) 
	{
		//描画する時間より長くなったら段々透明にしていく
		m_alphaTime += GameTime().GetDeltaFrameTime();
		float alpha = 1.0f - m_alphaTime;
		if (alpha < 0.0f)
		{
			//透明になった
			Delete(this);
			return;
		}
		for (int i = 0; i < EnDigit::enDigit_Num; i++)
		{
			m_number[i].SetAlpha(alpha);
		}
	}
}

void CDamageNumber::PostAfterDraw()
{
	for (int i = 0; i < EnDigit::enDigit_Num; i++)
	{
		m_number[i].Draw();
	}
}

void CDamageNumber::DamageCalculation()
{
	//ダメージ計算
	SWeaponStatus weaponStatus = GetPlayer().GetWeaponManager().GetEquipWeapon()->GetEquipStatus();
	int playerStrength = GetPlayer().GetStatus().Strength + weaponStatus.attack;
	int enemyDefence = m_enemy->GetStatus().defense;
	int damage = playerStrength - enemyDefence;
	if (damage < 0)
	{
		damage = 0;
	}
	m_enemy->HpDamage(damage);

	//受けたダメージを取得
	damage %= 1000;
	if (damage / 100 > 0) 
	{
		//百の位を表示
		m_number[EnDigit::enDigit_Hundred].SetIsDraw(true);
		m_number[EnDigit::enDigit_Hundred].SetNumber(damage / 100);
	}
	else 
	{
		m_number[EnDigit::enDigit_Hundred].SetIsDraw(false);
	}
	damage %= 100;
	if (damage / 10 > 0) 
	{
		//十の位を表示
		m_number[EnDigit::enDigit_Ten].SetIsDraw(true);
		m_number[EnDigit::enDigit_Ten].SetNumber(damage / 10);
	}
	else 
	{
		//百の位も０の場合は十の位は表示しない
		if (m_number[EnDigit::enDigit_Hundred].GetIsDraw()) 
		{
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