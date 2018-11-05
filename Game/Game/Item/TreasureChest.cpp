#include "stdafx.h"
#include "TreasureChest.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"

void CTreasureChest::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/heart.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);

	//武器のステータスをランダムで決める
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= CWeapon::enWeaponNum;
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= 100;
	if (weaponNumber == CWeapon::EnPlayerWeapon::enSword)
	{
		//剣
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enSword;
		weaponAttack += 50;
	}
	else if (weaponNumber == CWeapon::EnPlayerWeapon::enLongSword)
	{
		//大剣
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enLongSword;
		weaponAttack += 70;
	}
	else if (weaponNumber == CWeapon::EnPlayerWeapon::enArrow)
	{
		//弓
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enArrow;
		weaponAttack += 20;
	}
	else if (weaponNumber == CWeapon::EnPlayerWeapon::enTwinSword)
	{
		//双剣
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enTwinSword;
		weaponAttack += 30;
	}
	m_weaponStatus.attack = weaponAttack;
}

bool CTreasureChest::Start()
{
	CVector3 popSpeed = CVector3::Zero;
	popSpeed.y = m_speed / 2.0f;
	m_characterController.SetMoveSpeed(popSpeed);

	return true;
}

void CTreasureChest::Update()
{
	if (GetPlayer().GetIsDied() || m_timer > m_itemDeadTime)
	{
		//プレイヤーが死亡した又は一定時間で削除
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//移動速度を取得
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();

	//地面に接地したら止める
	if (!m_popEnd && m_characterController.IsOnGround()) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		m_popEnd = true;
	}

	//キャラクターコントローラーに移動速度を設定
	m_characterController.SetMoveSpeed(moveSpeed);

	//プレイヤーとの距離を計算
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	float length = toPlayer.Length();
	if (m_popEnd && length < 2.0f && Pad().IsTriggerButton(enButtonA)) {
		GetPlayer().AddEquipList(m_weaponStatus);
		Delete(this);
	}

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CTreasureChest::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}