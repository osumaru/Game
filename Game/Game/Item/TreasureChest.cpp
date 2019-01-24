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
#include"GameItem/CEquipItem.h"

void CTreasureChest::Init(CVector3 position)
{
	//���f���̏�����
	m_skinModel.Load(L"Assets/modelData/Chest.cmo");
	//���W��ݒ�
	m_position = position;
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(0.6f, 0.4f, m_position);
	m_characterController.SetUserIndex(enCollisionAttr_Item);
}

bool CTreasureChest::Start()
{
	//�|�b�v�����鋗���Ə�����̃X�s�[�h��ݒ�
	float distance = 0.0f;
	float popUpSpeed = 2.0f;
	//�����_���Ƀ|�b�v������
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
		const float GetVolume = 0.3f;
		CSoundSource* GetSound = New<CSoundSource>(0);
		GetSound->Init("Assets/sound/Battle/TresureSE.wav");
		GetSound->Play(false);
		GetSound->SetVolume(GetVolume);
		//����̃X�e�[�^�X�����߂�
		DesideWeaponStatus();
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
	//�A�C�e���̃f�[�^���擾
	//������̎擾
	wchar_t* itemName;
	wchar_t* textureFileName;
	CEquipItem* nItem = GetSceneManager().GetFade()->GetLoadScene()->GetEquipItemData();
	//������̓��A�x��Normal�̕��킩�烉���_���ŕ�����擾����R�[�h
	int num = nItem->GetNormalEquipItemList(Random().GetRandSInt() % nItem->GetNormalEquipItemListSize());
	//����̃^�C�v�̎擾
	int weaponNumber = nItem->GetItemStatus_ItemId(num).WeaponType;
	//����̖��O�̎擾
	itemName = nItem->GetItemStatus_ItemId(num).ItemName;
	//�����UI���̎擾(������)
	textureFileName = nItem->GetItemStatus(num).ItemSprite;
	int weaponAttack = nItem->GetItemStatus_ItemId(num).ItemEffect;
	
	
	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//��
		m_inventoryEquip = std::make_unique<CInventorySword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//�匕
		m_inventoryEquip = std::make_unique<CInventoryLargeSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//�|
		m_inventoryEquip = std::make_unique<CInventoryBow>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//�o��
		m_inventoryEquip = std::make_unique<CInventoryTwinSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
	}
	weaponStatus.attack = weaponAttack;
	m_inventoryEquip->SetEquipStatus(weaponStatus);
	m_inventoryEquip->Init(itemName, textureFileName);
}
