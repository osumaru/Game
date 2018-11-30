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
	//����̃X�e�[�^�X�����߂�
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
		//�v���C���[�����S�������͈�莞�Ԃō폜
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	//�n�ʂɐڒn���Ă��邩����
	bool isPopEnd = m_characterController.IsOnGround();
	//�v���C���[�Ƃ̋������v�Z
	bool isPickUp = PickUp(isPopEnd, 2.0f);
	if (isPickUp && Pad().IsTriggerButton(enButtonA)) {
		//�E�����Ƃ��ł���
		CEquipInventory::AddEquipList(m_weaponStatus);
		Delete(this);
	}

	//�L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
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
	//����̃X�e�[�^�X�������_���Ō��߂�
	SBasicWeaponStatus basicWeaponStatus;
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= enWeaponNum;
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= basicWeaponStatus.basicAttack;
	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//��
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
		weaponAttack += basicWeaponStatus.swordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//�匕
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
		weaponAttack += basicWeaponStatus.longSwordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//�|
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
		weaponAttack += basicWeaponStatus.arrowAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//�o��
		m_weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
		weaponAttack += basicWeaponStatus.twinSwordAttack;
	}
	m_weaponStatus.attack = weaponAttack;
}
