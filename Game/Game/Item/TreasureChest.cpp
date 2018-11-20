#include "stdafx.h"
#include "TreasureChest.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"

void CTreasureChest::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/heart.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);

	//����̃X�e�[�^�X�������_���Ō��߂�
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= enWeaponNum;
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= 100;
	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//��
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
		weaponAttack += 50;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//�匕
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
		weaponAttack += 70;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//�|
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
		weaponAttack += 20;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//�o��
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
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
		//�v���C���[�����S�������͈�莞�Ԃō폜
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();

	//�n�ʂɐڒn������~�߂�
	if (!m_popEnd && m_characterController.IsOnGround()) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		m_popEnd = true;
	}

	//�L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
	m_characterController.SetMoveSpeed(moveSpeed);

	//�v���C���[�Ƃ̋������v�Z
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	float length = toPlayer.Length();
	if (m_popEnd && length < 2.0f && Pad().IsTriggerButton(enButtonA)) {
		GetPlayer().GetWeaponManager().AddEquipList(m_weaponStatus);
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