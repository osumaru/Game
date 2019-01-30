#include "stdafx.h"
#include "WeaponSelect.h"
#include "../../Player/Player.h"

void CWeaponSelect::Init()
{
	crossKeyPos = { -520.0f, -240.0f };
	const float ICON_SIZE = 70.0f;
	size = { ICON_SIZE, ICON_SIZE };
	const float CROSS_KEY_SIZE = 50.0f;
	CVector2 crossKeySize = { CROSS_KEY_SIZE, CROSS_KEY_SIZE };
	const float KEY_WEAPON_SPACE = 63.0f;
	//武器選択のスプライトを初期化
	//剣
	m_weaponTexture[enWeaponSword] = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
	m_weapon[enWeaponSword].Init(m_weaponTexture[enWeaponSword]);
	m_weapon[enWeaponSword].SetPosition({ crossKeyPos.x , crossKeyPos.y + KEY_WEAPON_SPACE });
	m_weapon[enWeaponSword].SetSize(size);
	//大剣
	m_weaponTexture[enWeaponLongSword] = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
	m_weapon[enWeaponLongSword].Init(m_weaponTexture[enWeaponLongSword]);
	m_weapon[enWeaponLongSword].SetPosition({ crossKeyPos.x + KEY_WEAPON_SPACE, crossKeyPos.y });
	m_weapon[enWeaponLongSword].SetSize(size);
	//双剣
	m_weaponTexture[enWeaponTwinSword] = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
	m_weapon[enWeaponTwinSword].Init(m_weaponTexture[enWeaponTwinSword]);
	m_weapon[enWeaponTwinSword].SetPosition({ crossKeyPos.x - KEY_WEAPON_SPACE, crossKeyPos.y });
	m_weapon[enWeaponTwinSword].SetSize(size);
	//弓
	m_weaponTexture[enWeaponArrow] = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
	m_weapon[enWeaponArrow].Init(m_weaponTexture[enWeaponArrow]);
	m_weapon[enWeaponArrow].SetPosition({ crossKeyPos.x, crossKeyPos.y - KEY_WEAPON_SPACE });
	m_weapon[enWeaponArrow].SetSize(size);
	
	m_weaponChoice.Init(TextureResource().LoadTexture(L"Assets/sprite/weaponChoice.png"));
	m_weaponChoice.SetSize(size);
	ChangeWeapon();
	//十字キー
	m_crossKeyTexture = TextureResource().LoadTexture(L"Assets/sprite/crossKey.png");
	m_crossKey.Init(m_crossKeyTexture);
	m_crossKey.SetPosition(crossKeyPos);
	m_crossKey.SetSize(crossKeySize);
}

void CWeaponSelect::Update()
{
	//武器変更
	ChangeWeapon();

}

void CWeaponSelect::PostAfterDraw()
{
	m_weapon[enWeaponSword].Draw();
	m_weapon[enWeaponLongSword].Draw();
	m_weapon[enWeaponTwinSword].Draw();
	m_weapon[enWeaponArrow].Draw();
	m_weaponChoice.Draw();
	m_crossKey.Draw();
}

void CWeaponSelect::ChangeWeapon()
{
	//プレイヤーが装備している武器の種類を取得
	weaponNumber = GetPlayer().GetWeaponManager().GetCurrentState();
	CVector2 pos = m_weapon[weaponNumber].GetPosition();
	m_weaponChoice.SetPosition(pos);
}