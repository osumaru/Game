#include "stdafx.h"
#include "TreasureChest.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../UI/Menu/EquipInventory.h"
#include "../UI/GetItem/GetItem.h"
#include "../Scene/SceneManager.h"
#include "../Player/Weapon/WeaponCommon.h"
#include "../Item/InventoryItem/InventorySword.h"
#include "../Item/InventoryItem/InventoryLargeSword.h"
#include "../Item/InventoryItem/InventoryBow.h"
#include "../Item/InventoryItem/InventoryTwinSword.h"
#include"GameItem/CEquipItem.h"

void CTreasureChest::Init(CVector3 position, CQuaternion rotation, bool isMapItem, EnDropType dropType)
{
	//モデルの初期化
	m_skinModel.Load(L"Assets/modelData/TresureBox.cmo");
	m_skinModel.LoadNormalmap(L"Assets/modelData/Interior/box_01_normal.tga");
	m_skinModel.SetIsDiffuse(true);
	m_skinModel.SetSpecularPower(0.3f);
	m_light.SetAmbientLight({ 0.8f ,0.8f,0.8f,1.0f });
	m_skinModel.SetLight(m_light);
	//座標を設定
	m_position = position;
	m_rotation = rotation;
	//キャラクターコントローラーを初期化
	//m_characterController.Init(1.0f, 0.5f, m_position);
	//m_characterController.SetUserIndex(enCollisionAttr_Item);
	//マップに配置するか
	m_isMapItem = isMapItem;
	m_dropType = dropType;

	SRigidBodyInfo rInfo;
	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	CQuaternion multi = CQuaternion::Identity;
	rInfo.rot.Multiply(multi);
	//AABBの作成
	{
		CMatrix rotMat;
		rotMat.MakeRotationFromQuaternion(multi);
		CMeshCollider mesh;
		mesh.CreateCollider(&m_skinModel);
		CVector3 boxsize = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
		CVector3 pos = (mesh.GetAabbMax() + mesh.GetAabbMin()) / 2.0f;
		pos.Mul(rotMat);
		rInfo.pos = pos + m_position;
		m_boxCollider.reset(new CBoxCollider);
		m_boxCollider->Create({ boxsize.x,boxsize.y,boxsize.z });
		rInfo.collider = m_boxCollider.get();
		m_rigidBody.reset(new CRigidBody);
		m_rigidBody->Create(rInfo);
	}
}

bool CTreasureChest::Start()
{
	if (!m_isMapItem) 
	{
		//ポップさせる距離と上方向のスピードを設定
		float distance = 0.0f;
		float popUpSpeed = 2.0f;
		//ランダムにポップさせる
		RamdomPop(distance, popUpSpeed);
	}

	return true;
}

void CTreasureChest::Update()
{
	if (GetSceneManager().GetSceneChange() || 
		(!m_isMapItem && m_timer > m_deadTime))
	{
		//プレイヤーが死亡した又は一定時間で削除
		Delete(this);
		return;
	}

	if (!m_isMapItem)
	{
		m_timer += GameTime().GetDeltaFrameTime();
	}

	//移動速度を取得
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	//地面に接地しているか判定
	bool isPopEnd = true;//m_characterController.IsOnGround();
	//プレイヤーとの距離を計算
	bool isPickUp = PickUp(isPopEnd, 2.0f);
	//拾うことができるか
	if (isPickUp) 
	{
		if (!m_itemDrawCount) 
		{
			GetSceneManager().GetGameScene().GetGetItem()->AddDrawCount();
			m_itemDrawCount = true;
		}
		if (Pad().IsTriggerButton(enButtonA))
		{
			const float GetVolume = 0.3f;
			CSoundSource* GetSound = New<CSoundSource>(0);
			GetSound->Init("Assets/sound/Battle/TresureSE.wav");
			GetSound->Play(false);
			GetSound->SetVolume(GetVolume);
			//武器のステータスを決める
			DesideWeaponStatus();
			CEquipInventory::AddEquipList(std::move(m_inventoryEquip));
			GetSceneManager().GetGameScene().GetGetItem()->SubtractDrawCount();
			m_itemDrawCount = false;
			GetPlayer().SetIsAction(false);
			Delete(this);
		}
	}
	else 
	{
		if (m_itemDrawCount)
		{
			GetSceneManager().GetGameScene().GetGetItem()->SubtractDrawCount();
			m_itemDrawCount = false;
		}
	}

	//キャラクターコントローラーに移動速度を設定
	/*m_characterController.SetMoveSpeed(moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();*/

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f },false);
}

void CTreasureChest::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_rigidBody->Draw();
}

void CTreasureChest::DesideWeaponStatus()
{
	SWeaponStatus weaponStatus;
	//アイテムのデータを取得
	//武器情報の取得
	wchar_t* itemName;
	wchar_t* textureFileName;
	CEquipItem* nItem = GetSceneManager().GetFade()->GetLoadScene()->GetEquipItemData();
	//↓これはレア度がNormalの武器からランダムで武器を取得するコード

	int num = 0;
	switch (m_dropType)
	{
	case EnDropType::enRandom:
	{
		int probability = 0;
		probability = Random().GetRandSInt() % 100;

		if (probability <= 90 && probability >= 0)
		{

			num = nItem->GetNormalEquipItemList((Random().GetRandInt() % (nItem->GetNormalEquipItemListSize() - 1)));
		}
		else if (probability <= 98 && probability > 90)
		{
			num = nItem->GetRareItemList(Random().GetRandSInt() % max(0, (nItem->GetRareEquipItemListSize() - 1)));
		}
		else
		{
			num = nItem->GetLegendEquipItemList(Random().GetRandSInt() % max(0, (nItem->GetLegendEquipItemListSize() - 1)));
		}
	}
		break;
	case EnDropType::enNormal:
		num = nItem->GetNormalEquipItemList((Random().GetRandInt() % (nItem->GetNormalEquipItemListSize() - 1)));
		break;
	case EnDropType::enRare:
		num = nItem->GetRareItemList(Random().GetRandSInt() % max(0, (nItem->GetRareEquipItemListSize() - 1)));
		break;
	case EnDropType::enLegend:
		num = nItem->GetLegendEquipItemList(Random().GetRandSInt() % max(0, (nItem->GetLegendEquipItemListSize() - 1)));
		break;
	case EnDropType::enSpecial:

		break;
	}

	//武器のタイプの取得
	int weaponNumber = nItem->GetItemStatus_ItemId(num).WeaponType;
	//武器の名前の取得
	itemName = nItem->GetItemStatus_ItemId(num).ItemName;
	//武器のUI情報の取得(文字列)
	textureFileName = nItem->GetItemStatus(num).ItemSprite;
	int weaponAttack = nItem->GetItemStatus_ItemId(num).ItemEffect;

	if (weaponNumber == EnPlayerWeapon::enWeaponSword)
	{
		//剣
		m_inventoryEquip = std::make_unique<CInventorySword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponSword;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponLongSword)
	{
		//大剣
		m_inventoryEquip = std::make_unique<CInventoryLargeSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponLongSword;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponArrow)
	{
		//弓
		m_inventoryEquip = std::make_unique<CInventoryBow>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponArrow;
	}
	else if (weaponNumber == EnPlayerWeapon::enWeaponTwinSword)
	{
		//双剣
		m_inventoryEquip = std::make_unique<CInventoryTwinSword>();
		weaponStatus.weaponNum = EnPlayerWeapon::enWeaponTwinSword;
	}
	weaponStatus.attack = weaponAttack;
	m_inventoryEquip->SetEquipStatus(weaponStatus);
	m_inventoryEquip->Init(itemName, textureFileName);
}
