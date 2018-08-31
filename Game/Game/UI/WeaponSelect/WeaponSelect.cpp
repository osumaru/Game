#include "stdafx.h"
#include "WeaponSelect.h"

void WeaponSelect::Init()
{
	crossKeyPos = { -520.0f, -240.0f };
	size = { 50.0f,50.0f };

	m_weaponTexture[Sword].Load(L"Assets/sprite/sword.png");
	m_weapon[Sword].Init(&m_weaponTexture[Sword]);
	m_weapon[Sword].SetPosition({ crossKeyPos.x , crossKeyPos.y + size.y });
	m_weapon[Sword].SetSize(size);

	m_weaponTexture[LargeSword].Load(L"Assets/sprite/largeSword.png");
	m_weapon[LargeSword].Init(&m_weaponTexture[LargeSword]);
	m_weapon[LargeSword].SetPosition({ crossKeyPos.x + size.x, crossKeyPos.y });
	m_weapon[LargeSword].SetSize(size);

	m_weaponTexture[TwinSword].Load(L"Assets/sprite/twinSword.png");
	m_weapon[TwinSword].Init(&m_weaponTexture[TwinSword]);
	m_weapon[TwinSword].SetPosition({ crossKeyPos.x - size.x, crossKeyPos.y });
	m_weapon[TwinSword].SetSize(size);

	m_weaponTexture[Bow].Load(L"Assets/sprite/bow.png");
	m_weapon[Bow].Init(&m_weaponTexture[Bow]);
	m_weapon[Bow].SetPosition({ crossKeyPos.x, crossKeyPos.y - size.y });
	m_weapon[Bow].SetSize(size);

	for (int i = 0; i < WeaponNum; i++) {
		if (i == Sword) {
			m_selectFlag[i] = true;
		}
		else {
			m_selectFlag[i] = false;
		}
	}

	m_crossKeyTexture.Load(L"Assets/sprite/crossKey.png");
	m_crossKey.Init(&m_crossKeyTexture);
	m_crossKey.SetPosition(crossKeyPos);
	m_crossKey.SetSize({ size.x - 10.0f, size.y - 10.0f });

	m_LBButtonTexture.Load(L"Assets/sprite/LBButton.png");
	m_LBButton.Init(&m_LBButtonTexture);
	m_LBButton.SetPosition({ -580.0f, -140.0f });
	m_LBButton.SetSize({ 40.0f,30.0f });

	m_RBButtonTexture.Load(L"Assets/sprite/RBButton.png");
	m_RBButton.Init(&m_RBButtonTexture);
	m_RBButton.SetPosition({ -460.0f, -140.0f });
	m_RBButton.SetSize({ 40.0f,30.0f });

	
}

void WeaponSelect::Update()
{
	//武器変更
	ChangeWeapon();

	//武器が変更されていたら選択している武器を更新
	if (weaponNumber != weaponNumberOld) {
		m_selectFlag[weaponNumberOld] = false;
		weaponNumberOld = weaponNumber;
	}

	//選択した武器のUIの大きさを変える
	for (int i = 0; i < WeaponNum; i++) {
		if (m_selectFlag[i] == true){
			m_weapon[i].SetSize(size * 1.2f);
		}
		else {
			m_weapon[i].SetSize(size);
		}
	}
}

void WeaponSelect::Draw()
{
	m_weapon[Sword].Draw();
	m_weapon[LargeSword].Draw();
	m_weapon[TwinSword].Draw();
	m_weapon[Bow].Draw();
	m_crossKey.Draw();
	m_LBButton.Draw();
	m_RBButton.Draw();
}

void WeaponSelect::ChangeWeapon()
{
	//十字キーで武器を変更する
	if (GetPad().IsTriggerButton(enButtonUp)) {
		weaponNumber = Sword;
	}
	else if (GetPad().IsTriggerButton(enButtonRight)) {
		weaponNumber = LargeSword;
	}
	else if (GetPad().IsTriggerButton(enButtonDown)) {
		weaponNumber = Bow;		
	}
	else if (GetPad().IsTriggerButton(enButtonLeft)) {
		weaponNumber = TwinSword;		
	}

	//RBボタンかLBボタンで武器を変更する
	if (GetPad().IsTriggerButton(enButtonRB)) {
		weaponNumber++;
		if (weaponNumber > TwinSword) {
			weaponNumber = Sword;
		}
	}
	else if (GetPad().IsTriggerButton(enButtonLB)) {
		weaponNumber--;
		if (weaponNumber < Sword){
			weaponNumber = TwinSword;
		}
	}

	m_selectFlag[weaponNumber] = true;
}