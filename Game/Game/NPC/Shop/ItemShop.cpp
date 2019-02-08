#include "stdafx.h"
#include "ItemShop.h"
#include "../../Player/Player.h"
#include "../../Item/InventoryItem/IInventoryItem.h"
#include "../../Item/InventoryItem/InventoryRecoveryItem.h"
#include "../../UI/Fade/LoadScene.h"
#include "../../UI/Menu/ItemInventory.h"


CItemShop::CItemShop()
{
}


CItemShop::~CItemShop()
{
}

void CItemShop::Init(const CVector3 position, const CQuaternion rotation)
{
	
	m_position = position;
	m_rotation = rotation;
	wchar_t* animClip[] = { L"Assets/modelData/ShopgirlStand.tka" };
	m_animation.Init(animClip, 1);
	m_animation.SetLoopFlg(0, true);
	m_skinModel.Load(L"Assets/modelData/Shopgirl.cmo", &m_animation);
	m_animation.Play(0);

	//テクスチャ及びスプライト関係の初期化
	{
		m_backTexture = TextureResource().LoadTexture(L"Assets/sprite/Back_Texture.png");
		m_backSprite.Init(m_backTexture);
		m_backSprite.SetPosition({ 10.0f,95.0f });
		m_backSprite.SetSize({ 625.0f,325.0f });


		m_shopSelectTexture[0] = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/Buy.png");
		m_shopSelect[0].Init(m_shopSelectTexture[0]);
		m_shopSelectTexture[1] = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/Execute.png");
		m_shopSelect[1].Init(m_shopSelectTexture[1]);
		for (int num = 0;num < SELECT_TEX_ELEMENT;num++)
		{
			m_shopSelect[num].SetPosition(m_shopSelectPosition);
			m_shopSelect[num].SetSize(m_shopSelectSize);
			m_shopSelectPosition.y -= 100.0f;
		}

		m_shopSelectPenTexture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Select2.png");
		m_shopSelectPen.Init(m_shopSelectPenTexture);
		m_shopSelectPen.SetPosition(m_shopSelectPenPosition);
		m_shopSelectPen.SetSize(m_shopSelectPenSize);

		m_selectItemTexture = TextureResource().LoadTexture(L"Assets/sprite/ShopUI/SelectItem.png");
		m_selectItemSprite.Init(m_selectItemTexture);
		m_selectItemSprite.SetPosition(m_slectItemTexPos);
		m_selectItemSprite.SetSize(m_selectItemTexSize);


		m_quickItem.Start();

		wchar_t filePath[256];
		for (int num = 0; num < ITEM_ELEMENT;num++)
		{
			int RandomID = Random().GetRandInt() % 6;// 9 + 1;
			m_items[num].ItemStatus = m_quickItem.GetItemStatus(RandomID);
			swprintf(filePath, L"Assets/sprite/Item/Quick/Item_%d.png", m_items[num].ItemStatus.ItemID);
			m_items[num].ItemTexture = TextureResource().LoadTexture(filePath);
			m_items[num].ItemSprite.Init(m_items[num].ItemTexture);
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
}

void CItemShop::Update()
{
	ShopUpdate();
	if (!m_isTransaction) { return; };
	if (GetPlayer().BuyMoney(m_items[m_lineupSelectNumber + 101].ItemStatus.Itemprice))
	{
		std::unique_ptr<IInventoryItem> inventoryItem = std::make_unique<CInventoryRecoveryItem>();
		inventoryItem->Init();
		CItemInventory::AddItemList(std::move(inventoryItem));
		CSoundSource* se = New<CSoundSource>(0);
		//se->Init("Assets/sound/Shop/BuySe.wav");
		se->SetVolume(1.0f);
		se->Play(false);
		

	}
	m_isTransaction = false;
	
}

void CItemShop::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	
}
void CItemShop::PostAfterDraw()
{
	if(!m_isSelectDraw && !m_isShoplineupDraw) { return; }

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
		m_items[num].ItemSprite.Draw();
		
	}

}