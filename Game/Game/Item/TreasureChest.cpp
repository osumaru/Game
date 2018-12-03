#include "stdafx.h"
#include "TreasureChest.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../UI/Menu/EquipInventory.h"

void CTreasureChest::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/Chest.cmo");
	m_position = position;
	m_position.y += 5.0f;
	m_characterController.Init(0.6f, 0.4f, m_position);
	//武器のステータスを決める
	DesideWeaponStatus();
}

bool CTreasureChest::Start()
{
	float distance = 0.0f;
	float popUpSpeed = 2.0f;
	RamdomPop(distance, popUpSpeed);

	return true;
}

void CTreasureChest::Update()
{
	if (GetPlayer().GetIsDied() || m_timer > m_deadTime)
	{
		//プレイヤーが死亡した又は一定時間で削除
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//移動速度を取得
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	//地面に接地しているか判定
	bool isPopEnd = m_characterController.IsOnGround();
	//プレイヤーとの距離を計算
	bool isPickUp = PickUp(isPopEnd, 2.0f);
	if (isPickUp && Pad().IsTriggerButton(enButtonA)) {
		//拾うことができる
		CEquipInventory::AddEquipList(m_weaponStatus);
		Delete(this);
	}

	//キャラクターコントローラーに移動速度を設定
	m_characterController.SetMoveSpeed(moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CTreasureChest::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CTreasureChest::DesideWeaponStatus()
{
	//武器のステータスをランダムで決める
	SBasicWeaponStatus basicWeaponStatus;
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= enWeaponNum;
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= basicWeaponStatus.basicAttack;
	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//剣
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
		weaponAttack += basicWeaponStatus.swordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//大剣
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
		weaponAttack += basicWeaponStatus.longSwordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//弓
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
		weaponAttack += basicWeaponStatus.arrowAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//双剣
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
		weaponAttack += basicWeaponStatus.twinSwordAttack;
	}
	m_weaponStatus.attack = weaponAttack;
}
