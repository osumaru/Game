#include "stdafx.h"
#include "WeaponShop.h"
#include "../../Player/Player.h"
#include "../../UI/Menu/EquipInventory.h"
#include "../../UI/Fade/LoadScene.h"
#include "../../Scene/SceneManager.h"
#include "../../Item/InventoryItem/InventorySword.h"
#include "../../Item/InventoryItem/InventoryLargeSword.h"
#include "../../Item/InventoryItem/InventoryBow.h"
#include "../../Item/InventoryItem/InventoryTwinSword.h"

CWeaponShop::CWeaponShop()
{
	SetIsActive(false);
}


CWeaponShop::~CWeaponShop()
{
}

void CWeaponShop::Init(const CVector3 position, const CQuaternion rotation, EShop shopType, const int element)
{
	m_shopType = shopType;
	//AddFile(L"Assets/sprite/shopData");
	//LoadFile(L"Assets/sprite/shopData");
	m_position = position;
	m_rotation = rotation;
	m_element = element;
	SRigidBodyInfo rInfo;

	rInfo.mass = 0.0f;
	rInfo.pos = m_position;
	rInfo.rot = m_rotation;
	CQuaternion multi = CQuaternion::Identity;
	rInfo.rot.Multiply(multi);

	wchar_t* animClip[] = { L"Assets/modelData/ShopgirlStand.tka" };
	m_animation.Init(animClip, 1);
	m_animation.SetLoopFlg(0, true);
	m_skinmodelNpc.Load(L"Assets/modelData/Shopgirl.cmo", &m_animation);
	m_animation.Play(0);
	m_skinModel.Load(L"Assets/modelData/roten.cmo",NULL);
	m_skinModel.Update(m_position, m_rotation, m_scale, false);
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
	

	//テクスチャ及びスプライト関係の初期化
	{
		m_backTexture = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/LineUp.png");
		m_backSprite.Init(m_backTexture);
		m_backSprite.SetPosition({ 0.0f,0.0f });
		m_backSprite.SetSize({ 730.0f,700.0f });


		m_shopSelectTexture[0] = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/Buy.png");
		m_shopSelect[0].Init(m_shopSelectTexture[0]);
		m_shopSelectTexture[1] = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/sell.png");
		m_shopSelect[1].Init(m_shopSelectTexture[1]);
		m_shopSelectTexture[2] = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/Execute.png");
		m_shopSelect[2].Init(m_shopSelectTexture[2]);
		for (int num = 0;num < SELECT_ITEM_ELEMENT;num++)
		{
			m_shopSelect[num].SetPosition(m_shopSelectPosition);
			m_shopSelect[num].SetSize(m_shopSelectSize);
			m_shopSelectPosition.y -= 65.0f;
		}

		m_shopSelectPenTexture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Select2.png");
		m_shopSelectPen.Init(m_shopSelectPenTexture);
		m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		m_shopSelectPen.SetSize(m_shopSelectPenSize);

		m_selectItemTexture = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/SelectItem.png");
		m_selectItemSprite.Init(m_selectItemTexture);
		m_selectItemSprite.SetPosition(m_slectItemTexPos);
		m_selectItemSprite.SetSize(m_selectItemTexSize);

		m_equipItem = GetSceneManager().GetFade()->GetLoadScene()->GetEquipItemData();
		for (int num = 0; num < EQUIP_ELEMENT;num++)
		{
			m_equipNameFont[num].Init(L"None");
			m_equipPriceFont[num].Init(L"None");
			m_equipItems[num].ItemTexture = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/SelectItem.png");
			m_equipItems[num].ItemSprite.Init(m_equipItems[num].ItemTexture);

		}
		wchar_t filePath[256];
		//商品情報の初期化
		LineupChange();
	}
	
	SetIsActive(true);
}
void CWeaponShop::LineupChange()
{
	wchar_t filePath[256];
	CVector2 texturePos = m_shopLineupPosition;
	CVector2 fontPos = m_fontPosition;
	int RandomID = 0;
	int randomElement = 0;
	bool loop = false;
	for (int num = 0; num < EQUIP_ELEMENT;num++)
	{
		if (GetPlayer().GetStatus().Level >= 10)
		{
			randomElement = (Random().GetRandInt() % (m_equipItem->GetRareEquipItemListSize() - 1));
			RandomID = m_equipItem->GetRareItemList(randomElement);
		}
		else
		{
				randomElement = (Random().GetRandInt() % (m_equipItem->GetNormalEquipItemListSize() - 1));
				RandomID = m_equipItem->GetNormalEquipItemList(randomElement);
		}
		//アイテムのIDを取得
		m_equipItems[num].ItemStatus = m_equipItem->GetItemStatus_ItemId(RandomID);
		float plus = (float)(Random().GetRandInt() % 5 )/ 10;
		m_equipItems[num].ItemStatus.ItemEffect += (int)m_equipItems[num].ItemStatus.ItemEffect * plus;
		m_equipItems[num].ItemStatus.Itemprice += (int)m_equipItems[num].ItemStatus.Itemprice * plus;
		//スプライトの設定
		m_equipItems[num].ItemTexture = TextureResource().LoadTexture(m_equipItems[num].ItemStatus.ItemSprite);
		m_equipItems[num].ItemSprite.SetTexture(m_equipItems[num].ItemTexture);
		m_equipItems[num].ItemSprite.SetSize(m_shopLineupTexSize);
		m_equipItems[num].ItemSprite.SetPosition(texturePos);
		texturePos.y -= SHOPLINEUP_POSITION_OFFSET.y;
		swprintf(m_filePath, m_equipItems[num].ItemStatus.ItemName);
		m_equipNameFont[num].SetString(m_filePath);
		m_equipNameFont[num].SetPosition({ fontPos.x + FONT_POSITION_OFFSET.x, fontPos.y });
		swprintf(m_filePath, L"     %dG", m_equipItems[num].ItemStatus.Itemprice);
		m_equipPriceFont[num].SetString(m_filePath);
		m_equipPriceFont[num].SetPosition({ fontPos.x + FONT_POSITION_OFFSET.x * 2, fontPos.y });
		fontPos.y -= FONT_POSITION_OFFSET.y;
	}
}

void CWeaponShop::InitLineUp()
{

}

void CWeaponShop::Update()
{
	ShopUpdate();
	m_changeTime += GameTime().GetDeltaFrameTime();
	if (m_changeTime >60.0f)
	{
		m_minuteCount += 1;
		m_changeTime = 0.0f;
		if (m_minuteCount > LINEUP_CHANGE_TIME)
		{
			LineupChange();
			m_minuteCount = 0;
		}
		

	}
	if (!m_isTransaction) { return; };
	if (GetPlayer().BuyMoney(m_equipItems[m_lineupSelectNumber].ItemStatus.Itemprice) && GetEquipList().IsSpaceEquipList())
	{
		
		wchar_t* itemName = m_equipItems[m_lineupSelectNumber].ItemStatus.ItemName;
		wchar_t* textureFileName = m_equipItems[m_lineupSelectNumber].ItemStatus.ItemSprite;
		SWeaponStatus weapons;

		weapons.weaponNum = (EnPlayerWeapon)m_equipItems[m_lineupSelectNumber].ItemStatus.WeaponType;
		switch (m_equipItems[m_lineupSelectNumber].ItemStatus.ItemEffectPlayerStatus)
		{
			
		case EnIemEffectPlayerStatus::Strength:
			weapons.attack = m_equipItems[m_lineupSelectNumber].ItemStatus.ItemEffect;
			break;
		case EnIemEffectPlayerStatus::Defense:
			weapons.diffence = m_equipItems[m_lineupSelectNumber].ItemStatus.ItemEffect;
			break;
		case EnIemEffectPlayerStatus::Health:

			break;
		}
		//インベントリに入れる用の装備(スプライト)を作る
		std::unique_ptr<IInventoryEquip> inventoryEquip;
		switch (weapons.weaponNum)
		{
		case EnPlayerWeapon::enWeaponSword:			//剣
			inventoryEquip = std::make_unique<CInventorySword>();
			break;
		case EnPlayerWeapon::enWeaponLongSword:		//大剣
			inventoryEquip = std::make_unique<CInventoryLargeSword>();
			break;
		case EnPlayerWeapon::enWeaponArrow:			//弓
			inventoryEquip = std::make_unique<CInventoryBow>();
			break;
		case EnPlayerWeapon::enWeaponTwinSword:		//双剣
			inventoryEquip = std::make_unique<CInventoryTwinSword>();
			break;
		}
		inventoryEquip->Init(itemName, textureFileName);
		inventoryEquip->SetEquipStatus(weapons);
		inventoryEquip->SetItemStatus(m_equipItems[m_lineupSelectNumber].ItemStatus);
		GetEquipList().AddEquipList(std::move(inventoryEquip));

		CSoundSource* se = New<CSoundSource>(0);
		se->Init("Assets/sound/SystemSound/BuySe.wav");
		se->SetVolume(1.0f);
		se->Play(false);
		
	}
	m_isTransaction = false;
}

void CWeaponShop::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_skinmodelNpc.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CWeaponShop::PostAfterDraw()
{
	if (!m_isSelectDraw && !m_isShoplineupDraw) { return; }

	for (auto &SelectTex :m_shopSelect)
	{
		SelectTex.Draw();

	}
	m_shopSelectPen.Draw();

	if (!m_isShoplineupDraw) { return; }
	m_backSprite.Draw();
	m_selectItemSprite.Draw();
	for (auto &item: m_equipItems)
	{
		item.ItemSprite.Draw();
		
	}
	m_moneyBack.Draw();
	for (int num = 0; num < EQUIP_ELEMENT;num++)
	{
		m_equipNameFont[num].Draw();
		m_equipPriceFont[num].Draw();
	}
	m_money.Draw();
}