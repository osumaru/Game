#include "stdafx.h"
#include "TreasureChest.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../UI/Menu/EquipInventory.h"
#include "../Scene/SceneManager.h"
#include "../Player/Weapon/WeaponCommon.h"
#include "../Item/InventoryItem/InventorySword.h"
#include "../Item/InventoryItem/InventoryLargeSword.h"
#include "../Item/InventoryItem/InventoryBow.h"
#include "../Item/InventoryItem/InventoryTwinSword.h"

void CTreasureChest::Init(CVector3 position)
{
	m_skinModel.Load(L"Assets/modelData/Chest.cmo");
	m_position = position;
	m_characterController.Init(0.6f, 0.4f, m_position);
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
	//�E�����Ƃ��ł��邩
	if (isPickUp && Pad().IsTriggerButton(enButtonA)) {
		//����̃X�e�[�^�X�����߂�
		DesideWeaponStatus();
		m_inventoryEquip->Init();
		CEquipInventory::AddEquipList(std::move(m_inventoryEquip));
		GetPlayer().SetIsAction(false);
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
	SWeaponStatus weaponStatus;
	//����̃X�e�[�^�X�������_���Ō��߂�
	SBasicWeaponStatus basicWeaponStatus;
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= enWeaponNum;
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= basicWeaponStatus.basicAttack;
	//�A�C�e���̃f�[�^���擾
	/*
	CEquipItem* nItem = GetSceneManager().GetFade()->GetLoadScene()->GetEquipItemData();
	int num = nItem->GetNormalEquipItemList(Random().GetRandSInt() % nItem->GetNormalEquipItemListSize()) ;
	weaponNumber = nItem->GetItemStatus_ItemId(num).WeaponType;
	weaponAttack = nItem->GetItemStatus_ItemId(num).ItemEffect;
	*/
	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//��
		m_inventoryEquip = std::make_unique<CInventorySword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
		weaponAttack += basicWeaponStatus.swordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//�匕
		m_inventoryEquip = std::make_unique<CInventoryLargeSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
		weaponAttack += basicWeaponStatus.longSwordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//�|
		m_inventoryEquip = std::make_unique<CInventoryBow>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
		weaponAttack += basicWeaponStatus.arrowAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//�o��
		m_inventoryEquip = std::make_unique<CInventoryTwinSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
		weaponAttack += basicWeaponStatus.twinSwordAttack;
	}
	weaponStatus.attack = weaponAttack;
	m_inventoryEquip->SetEquipStatus(weaponStatus);
}
