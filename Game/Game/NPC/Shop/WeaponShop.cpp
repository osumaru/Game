#include "stdafx.h"
#include "WeaponShop.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../UI/Menu/EquipInventory.h"
#include "../../UI/Fade/LoadScene.h"
#include "../../Scene/SceneManager.h"

CWeaponShop::CWeaponShop()
{
	SetIsActive(false);
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
	wchar_t* animClip[] = { L"Assets/modelData/ShopgirlStand.tka" };
	m_animation.Init(animClip, 1);
	m_animation.SetLoopFlg(0, true);
	m_skinModel.Load(L"Assets/modelData/Shopgirl.cmo", &m_animation);
	m_animation.Play(0);

	//テクスチャ及びスプライト関係の初期化
	{
		m_backTexture.Load(L"Assets/sprite/ShopUI/LineUp.png");
		m_backSprite.Init(&m_backTexture);
		m_backSprite.SetPosition({ 0.0f,0.0f });
		m_backSprite.SetSize({ 650.0f,700.0f });


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

		m_equipItem = GetSceneManager().GetFade()->GetLoadScene()->GetEquipItemData();


		wchar_t filePath[256];
		//商品情報の初期化
		for (int num = 0; num < ITEM_ELEMENT;num++)
		{
			int RandomID = DEFAULT_WEAPON[num];//Random().GetRandInt() % 10;
			m_items[num].ItemStatus = m_equipItem->GetItemStatus(RandomID);
			swprintf(filePath, L"Assets/sprite/Item/Equip/Equip_%d.png", (int)m_items[num].ItemStatus.WeaponType);
			m_items[num].ItemTexture.Load(filePath);
			m_items[num].ItemSprite.Init(&m_items[num].ItemTexture);
			m_items[num].ItemSprite.SetSize(m_shopLineupTexSize);
			m_items[num].ItemSprite.SetPosition(m_shopLineupPosition);
			m_shopLineupPosition.y -= SHOPLINEUP_POSITION_OFFSET.y;
			swprintf(m_filePath, m_items[num].ItemStatus.ItemName);
			m_itemNameFont[num].Init(m_filePath);
			m_itemNameFont[num].SetPosition({ m_fontPosition.x + FONT_POSITION_OFFSET.x, m_fontPosition.y});
			swprintf(m_filePath,L"      %dG", m_items[num].ItemStatus.Itemprice);
			m_itemPriceFont[num].Init(m_filePath);
			m_itemPriceFont[num].SetPosition({ m_fontPosition.x + FONT_POSITION_OFFSET.x * 2, m_fontPosition.y });
			m_fontPosition.y -= FONT_POSITION_OFFSET.y;
		}
	}
	SetIsActive(true);
}
void CWeaponShop::LineupChange()
{
	wchar_t filePath[256];
	for (int num = 0; num < ITEM_ELEMENT;num++)
	{
		int RandomID = PICUP_WEAPON[num];
		m_items[num].ItemStatus = m_equipItem->GetItemStatus(RandomID);
		swprintf(filePath, L"Assets/sprite/Item/Equip/Equip_%d.png", (int)m_items[num].ItemStatus.WeaponType);
		m_items[num].ItemTexture.Load(filePath);
		m_items[num].ItemSprite.Init(&m_items[num].ItemTexture);
		m_items[num].ItemSprite.SetSize(m_shopLineupTexSize);
		m_items[num].ItemSprite.SetPosition(m_shopLineupPosition);
		m_shopLineupPosition.y -= SHOPLINEUP_POSITION_OFFSET.y;
		swprintf(m_filePath, m_items[num].ItemStatus.ItemName);
		m_itemNameFont[num].Init(m_filePath);
		m_itemNameFont[num].SetPosition({ m_fontPosition.x + FONT_POSITION_OFFSET.x, m_fontPosition.y });
		swprintf(m_filePath, L"     %dG", m_items[num].ItemStatus.Itemprice);
		m_itemPriceFont[num].Init(m_filePath);
		m_itemPriceFont[num].SetPosition({ m_fontPosition.x + FONT_POSITION_OFFSET.x * 2, m_fontPosition.y });
		m_fontPosition.y -= FONT_POSITION_OFFSET.y;
	}
}

void CWeaponShop::Update()
{
	ShopUpdate();
	if (!m_isTransaction) { return; };
	if (GetPlayer().BuyMoney(m_items[m_lineupSelectNumber + 1].ItemStatus.Itemprice))
	{
		SWeaponStatus weapons;

		weapons.weaponNum = (EnPlayerWeapon)m_items[m_lineupSelectNumber].ItemStatus.WeaponType;
		switch (m_items[m_lineupSelectNumber].ItemStatus.ItemEffectPlayerStatus)
		{
		case CEquipItem::EnIemEffectPlayerStatus::Strength:
			weapons.attack = m_items[m_lineupSelectNumber].ItemStatus.ItemEffect;
			break;
		case CEquipItem::EnIemEffectPlayerStatus::Defense:
			weapons.diffence = m_items[m_lineupSelectNumber].ItemStatus.ItemEffect;
			break;
		case CEquipItem::EnIemEffectPlayerStatus::Health:

			break;
		}
		CEquipInventory::AddEquipList(weapons);
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
}

void CWeaponShop::AfterDraw()
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
	for (auto &item:m_items)
	{
		item.ItemSprite.Draw();
		
	}
	for (int num = 0; num < ITEM_ELEMENT;num++)
	{
		m_itemNameFont[num].Draw();
		m_itemPriceFont[num].Draw();
	}
}