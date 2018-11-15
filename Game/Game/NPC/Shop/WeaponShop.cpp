#include "stdafx.h"
#include "WeaponShop.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Weapon.h"
#include "../../Player/Player.h"


CWeaponShop::CWeaponShop()
{
}


CWeaponShop::~CWeaponShop()
{
}
void CWeaponShop::Init(const CVector3 position, const CQuaternion rotation)
{
	//AddFile(L"Assets/sprite/shopData");
	//LoadFile(L"Assets/sprite/shopData");
	m_position = position;
	m_rotation = rotation;
	m_skinModel.Load(L"Assets/modelData/U2.cmo", NULL);

	//テクスチャ及びスプライト関係の初期化
	{
		m_backTexture.Load(L"Assets/sprite/Back_Texture.png");
		m_backSprite.Init(&m_backTexture);
		m_backSprite.SetPosition({ 10.0f,95.0f });
		m_backSprite.SetSize({ 625.0f,325.0f });


		m_shopSelectTexture[0].Load(L"Assets/sprite/ShopUI/Buy.png");
		m_shopSelect[0].Init(&m_shopSelectTexture[0]);
		m_shopSelectTexture[1].Load(L"Assets/sprite/ShopUI/Execute.png");
		m_shopSelect[1].Init(&m_shopSelectTexture[1]);
		for (int num = 0;num < SELECT_TEX_ELEMENT;num++)
		{
			m_shopSelect[num].SetPosition(m_shopSelectPosition);
			m_shopSelect[num].SetSize(m_shopSelectSize);
			m_shopSelectPosition.y -= 100.0f;
		}

		m_shopSelectPenTexture.Load(L"Assets/sprite/MenuUI/Select2.png");
		m_shopSelectPen.Init(&m_shopSelectPenTexture);
		m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		m_shopSelectPen.SetSize(m_shopSelectPenSize);

		m_selectItemTexture.Load(L"Assets/sprite/ShopUI/SelectItem.png");
		m_selectItemSprite.Init(&m_selectItemTexture);
		m_selectItemSprite.SetPosition(m_slectItemTexPos);
		m_selectItemSprite.SetSize(m_selectItemTexSize);

		m_equipItem.Start();


		wchar_t filePath[256];
		for (int num = 0; num < ITEM_ELEMENT;num++)
		{
			swprintf(m_items[num].ItemName,m_equipItem.GetItemStatus(num).ItemName);
			m_items[num].ItemID = m_equipItem.GetItemStatus(num).ItemID;
			swprintf(filePath, L"Assets/sprite/Item/Equip/Equip_%d.png", m_items[num].ItemID);
			m_items[num].Itemprice = m_equipItem.GetItemStatus(num).Itemprice;
			m_items[num].ItemTexture.Load(filePath);
			m_items[num].ItemSprite.Init(&m_items[num].ItemTexture);
			m_items[num].ItemSprite.SetSize(m_shopLineupTexSize);
			m_items[num].ItemSprite.SetPosition(m_shopLineupPosition);
			swprintf(m_filePath, m_items[num].ItemName);
			m_Itemfont[num].Init(m_filePath);
			m_Itemfont[num].SetPosition({ m_shopLineupPosition.x + SHOPLINEUP_POSITION_OFFSET.x, m_shopLineupPosition.y });
			m_shopLineupPosition.y -= SHOPLINEUP_POSITION_OFFSET.y;
		}
	}
	
}

void CWeaponShop::Update()
{
	ShopUpdate();
	if (!m_isTransaction) { return; };
	if (GetPlayer().BuyMoney(m_equipItem.GetItemStatus_ItemId(m_lineupSelectNumber + 1).Itemprice))
	{
		CWeapon::SWeaponStatus weapons;
		weapons.weaponNum = CWeapon::EnPlayerWeapon::enSword;
		switch (m_equipItem.GetItemStatus_ItemId(m_lineupSelectNumber + 1).ItemEffectPlayerStatus)
		{
		case CEquipItem::EnIemEffectPlayerStatus::Strength:
			weapons.attack = m_equipItem.GetItemStatus_ItemId(m_lineupSelectNumber + 1).ItemEffect;
			break;
		case CEquipItem::EnIemEffectPlayerStatus::Defense:
			weapons.diffence = m_equipItem.GetItemStatus_ItemId(m_lineupSelectNumber + 1).ItemEffect;
			break;
		case CEquipItem::EnIemEffectPlayerStatus::Health:

			break;
		}
		GetPlayer().AddEquipList(weapons);
		CSoundSource* se = New<CSoundSource>(0);
		se->Init("Assets/sound/Shop/BuySe.wav");
		se->SetVolume(1.0f);
		se->Play(false);
		
	}
	m_isTransaction = false;
}

void CWeaponShop::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CWeaponShop::AfterDraw()
{
	if (!m_isSelectDraw && !m_isShoplineupDraw) { return; }

	for (int num = 0;num < SELECT_TEX_ELEMENT;num++)
	{
		m_shopSelect[num].Draw();

	}
	m_shopSelectPen.Draw();

	if (!m_isShoplineupDraw) { return; }
	m_backSprite.Draw();
	m_selectItemSprite.Draw();
	for (int num = 0; num < ITEM_ELEMENT;num++)
	{
		m_items[num].ItemSprite.Draw();;
		m_Itemfont[num].Draw();
	}
	
}