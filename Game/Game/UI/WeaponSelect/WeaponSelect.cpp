#include "stdafx.h"
#include "WeaponSelect.h"
#include "../../Player/Player.h"

void CWeaponSelect::Init()
{
	crossKeyPos = { -520.0f, -240.0f };
	size = { 50.0f,50.0f };

	m_weaponTexture[enWeaponSword].Load(L"Assets/sprite/sword.png");
	m_weapon[enWeaponSword].Init(&m_weaponTexture[enWeaponSword]);
	m_weapon[enWeaponSword].SetPosition({ crossKeyPos.x , crossKeyPos.y + size.y });
	m_weapon[enWeaponSword].SetSize(size);

	m_weaponTexture[enWeaponLongSword].Load(L"Assets/sprite/largeSword.png");
	m_weapon[enWeaponLongSword].Init(&m_weaponTexture[enWeaponLongSword]);
	m_weapon[enWeaponLongSword].SetPosition({ crossKeyPos.x + size.x, crossKeyPos.y });
	m_weapon[enWeaponLongSword].SetSize(size);

	m_weaponTexture[enWeaponTwinSword].Load(L"Assets/sprite/twinSword.png");
	m_weapon[enWeaponTwinSword].Init(&m_weaponTexture[enWeaponTwinSword]);
	m_weapon[enWeaponTwinSword].SetPosition({ crossKeyPos.x - size.x, crossKeyPos.y });
	m_weapon[enWeaponTwinSword].SetSize(size);

	m_weaponTexture[enWeaponArrow].Load(L"Assets/sprite/bow.png");
	m_weapon[enWeaponArrow].Init(&m_weaponTexture[enWeaponArrow]);
	m_weapon[enWeaponArrow].SetPosition({ crossKeyPos.x, crossKeyPos.y - size.y });
	m_weapon[enWeaponArrow].SetSize(size);

	for (int i = 0; i < enWeaponNum; i++) {
		if (i == enWeaponSword) {
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

void CWeaponSelect::AfterDraw()
{
	m_weapon[enWeaponSword].Draw();
	m_weapon[enWeaponLongSword].Draw();
	m_weapon[enWeaponTwinSword].Draw();
	m_weapon[enWeaponArrow].Draw();
	m_crossKey.Draw();
	m_LBButton.Draw();
	m_RBButton.Draw();
}

void CWeaponSelect::ChangeWeapon()
{
	//十字キーで武器を変更する
	//if (Pad().IsTriggerButton(enButtonUp)) {
	//	weaponNumber = enSword;
	//}
	//else if (Pad().IsTriggerButton(enButtonRight)) {
	//	weaponNumber = enLongSword;
	//}
	//else if (Pad().IsTriggerButton(enButtonDown)) {
	//	weaponNumber = enArrow;
	//}
	//else if (Pad().IsTriggerButton(enButtonLeft)) {
	//	weaponNumber = enTwinSword;
	//}
	weaponNumber = GetPlayer().GetWeaponManager().GetCurrentState();
	//邪魔なので止めてます
	//RBボタンかLBボタンで武器を変更する
	/*if (Pad().IsTriggerButton(enButtonRB)) {
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
	*/
	m_selectFlag[weaponNumber] = true;
}