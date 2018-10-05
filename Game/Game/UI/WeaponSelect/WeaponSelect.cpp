#include "stdafx.h"
#include "WeaponSelect.h"

void CWeaponSelect::Init()
{
	crossKeyPos = { -520.0f, -240.0f };
	size = { 50.0f,50.0f };

	m_weaponTexture[enSword].Load(L"Assets/sprite/sword.png");
	m_weapon[enSword].Init(&m_weaponTexture[enSword]);
	m_weapon[enSword].SetPosition({ crossKeyPos.x , crossKeyPos.y + size.y });
	m_weapon[enSword].SetSize(size);

	m_weaponTexture[enLargeSword].Load(L"Assets/sprite/largeSword.png");
	m_weapon[enLargeSword].Init(&m_weaponTexture[enLargeSword]);
	m_weapon[enLargeSword].SetPosition({ crossKeyPos.x + size.x, crossKeyPos.y });
	m_weapon[enLargeSword].SetSize(size);

	m_weaponTexture[enTwinSword].Load(L"Assets/sprite/twinSword.png");
	m_weapon[enTwinSword].Init(&m_weaponTexture[enTwinSword]);
	m_weapon[enTwinSword].SetPosition({ crossKeyPos.x - size.x, crossKeyPos.y });
	m_weapon[enTwinSword].SetSize(size);

	m_weaponTexture[enBow].Load(L"Assets/sprite/bow.png");
	m_weapon[enBow].Init(&m_weaponTexture[enBow]);
	m_weapon[enBow].SetPosition({ crossKeyPos.x, crossKeyPos.y - size.y });
	m_weapon[enBow].SetSize(size);

	for (int i = 0; i < enWeaponNum; i++) {
		if (i == enSword) {
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

void CWeaponSelect::Update()
{
	//武器変更
	ChangeWeapon();

	//武器が変更されていたら選択している武器を更新
	if (weaponNumber != weaponNumberOld) {
		m_selectFlag[weaponNumberOld] = false;
		weaponNumberOld = weaponNumber;
	}

	//選択した武器のUIの大きさを変える
	for (int i = 0; i < enWeaponNum; i++) {
		if (m_selectFlag[i] == true){
			m_weapon[i].SetSize(size * 1.2f);
		}
		else {
			m_weapon[i].SetSize(size);
		}
	}
}

void CWeaponSelect::Draw()
{
	m_weapon[enSword].Draw();
	m_weapon[enLargeSword].Draw();
	m_weapon[enTwinSword].Draw();
	m_weapon[enBow].Draw();
	m_crossKey.Draw();
	m_LBButton.Draw();
	m_RBButton.Draw();
}

void CWeaponSelect::ChangeWeapon()
{
	//十字キーで武器を変更する
	if (Pad().IsTriggerButton(enButtonUp)) {
		weaponNumber = enSword;
	}
	else if (Pad().IsTriggerButton(enButtonRight)) {
		weaponNumber = enLargeSword;
	}
	else if (Pad().IsTriggerButton(enButtonDown)) {
		weaponNumber = enBow;		
	}
	else if (Pad().IsTriggerButton(enButtonLeft)) {
		weaponNumber = enTwinSword;		
	}

	//RBボタンかLBボタンで武器を変更する
	if (Pad().IsTriggerButton(enButtonRB)) {
		weaponNumber++;
		if (weaponNumber > enTwinSword) {
			weaponNumber = enSword;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLB)) {
		weaponNumber--;
		if (weaponNumber < enSword){
			weaponNumber = enTwinSword;
		}
	}

	m_selectFlag[weaponNumber] = true;
}