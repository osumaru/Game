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
	//モデルの初期化
	m_skinModel.Load(L"Assets/modelData/Chest.cmo");
	//座標を設定
	m_position = position;
	//キャラクターコントローラーを初期化
	m_characterController.Init(0.6f, 0.4f, m_position);
}

bool CTreasureChest::Start()
{
	//ポップさせる距離と上方向のスピードを設定
	float distance = 0.0f;
	float popUpSpeed = 2.0f;
	//ランダムにポップさせる
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
	//拾うことができるか
	if (isPickUp && Pad().IsTriggerButton(enButtonA)) {
		//武器のステータスを決める
		DesideWeaponStatus();
		CEquipInventory::AddEquipList(std::move(m_inventoryEquip));
		GetPlayer().SetIsAction(false);
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
	SWeaponStatus weaponStatus;
	//武器のステータスをランダムで決める
	SBasicWeaponStatus basicWeaponStatus;
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= enWeaponNum;
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= basicWeaponStatus.basicAttack;
	//アイテムのデータを取得

	//武器情報の取得
	/*
	CEquipItem* nItem = GetSceneManager().GetFade()->GetLoadScene()->GetEquipItemData();
	//↓これはレア度がNormalの武器からランダムで武器を取得するコード
	int num = nItem->GetNormalEquipItemList(Random().GetRandSInt() % nItem->GetNormalEquipItemListSize()) ;
	//武器のタイプの取得
	weaponNumber = nItem->GetItemStatus_ItemId(num).WeaponType;
	//武器の名前の取得
	//nItem->GetItemStatus_ItemId().ItemName();
	//武器のUI情報の取得(文字列)
	//nItem->GetItemStatus().ItemSprite();
	weaponAttack = nItem->GetItemStatus_ItemId(num).ItemEffect;
	*/
	////アイテムの名前と読み込むテクスチャファイルの名前を設定する//////
	wchar_t* itemName = L"ああああ";
	wchar_t* textureFileName = L"Assets/sprite/item/Equip/Equip_2.png";
	////////////////////////////////////////////////////////////////////
	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//剣
		m_inventoryEquip = std::make_unique<CInventorySword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
		weaponAttack += basicWeaponStatus.swordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//大剣
		m_inventoryEquip = std::make_unique<CInventoryLargeSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
		weaponAttack += basicWeaponStatus.longSwordAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//弓
		m_inventoryEquip = std::make_unique<CInventoryBow>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
		weaponAttack += basicWeaponStatus.arrowAttack;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//双剣
		m_inventoryEquip = std::make_unique<CInventoryTwinSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
		weaponAttack += basicWeaponStatus.twinSwordAttack;
	}
	weaponStatus.attack = weaponAttack;
	m_inventoryEquip->SetEquipStatus(weaponStatus);
	m_inventoryEquip->Init(itemName, textureFileName);
}
