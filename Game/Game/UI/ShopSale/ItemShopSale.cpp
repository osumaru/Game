#include "ItemShopSale.h"
#include "../../Item/InventoryItem/IInventoryItem.h"
#include "../Menu/ItemInventory.h"
#include "../../Scene/SceneManager.h"
#include "../../NPC/IShop.h"
#include "../Menu/Menu.h"
#include "../../Player/Player.h"


void CItemShopSale::Init()
{
	m_money.Init(L"0");
	m_money.SetPosition({ 100.0f, 100.0f });
	//インベントリの幅と高さを初期化
	m_width = 5;
	m_height = CItemList::m_itemLimit / m_width;
	//座標とサイズを初期化
	m_basePos = { -450.0f, 190.0f };
	m_size = { 100.0f, 100.0f };
	//項目を初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/item.png");
	m_headline.Init(texture);
	m_headline.SetPosition({ -450.0f, 310.0f });
	m_headline.SetSize({ 300.0f, 75.0f });
	//インベントリの背景を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/BackGround.png");
	m_backGround.Init(texture);
	m_backGround.SetPosition({ 0.0f, 30.0f });
	m_backGround.SetSize({ 1250.0f, 650.0f });
	//インベントリウィンドウを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_inventoryWindow.Init(texture);
	m_inventoryWindow.SetPosition({ -250.0f, -10.0f });
	m_inventoryWindow.SetSize({ 530.0f, 545.0f });
	//カーソルを初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//インベントリの枠を初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/Frame.png");
	for (int i = 0; i < CItemList::m_itemLimit; i++)
	{
		m_itemFrame[i].Init(texture);
		m_itemFrame[i].SetSize(m_size);
		CVector2 position = m_basePos;
		position.x += m_size.x * (i % m_width);
		position.y -= m_size.y * (i / m_width);
		m_itemFrame[i].SetPosition(position);
	}
	//ボタン表示の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonBackGround.png");
	m_buttonBackground.Init(texture);
	m_buttonBackground.SetSize({ 1200.0f, 40.0f });
	m_buttonBackground.SetPosition({ 0.0f, -325.0f });
	m_buttonBackground.SetAlpha(0.8f);

	const std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
	if (!itemList.empty())
	{
		//リストにアイテムがある
		int idx = 0;
		for (auto& item : itemList)
		{
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_size.x * (idx % m_width);
			position.y -= m_size.y * (idx / m_width);
			item->GetSprite()->SetPosition(position);
			item->GetSprite()->SetSize(m_size);
			idx++;
		}
	}
	//アイテムウィンドウの初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_itemWindow.Init(texture);
	m_itemWindow.SetPosition({ 320.0f, 180.0f });
	m_itemWindow.SetSize({ 300.0f, 100.0f });
	//アイテム名の初期化
	m_itemName.Init(L"");
	m_itemName.SetSize({ 0.7f,0.7f });
	m_itemName.SetPosition({ 270.0f, 190.0f });
}

void CItemShopSale::Update()
{
	int number = m_pointerNum;
	CVector2 position = m_pointer.GetPosition();
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//右にカーソルを動かす
		position.x += m_size.x;
		number++;
		if (position.x >= m_basePos.x + m_size.x * m_width)
		{
			//右端だった場合はそのまま
			position.x = m_basePos.x + m_size.x * (m_width - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		//左にカーソルを動かす
		position.x -= m_size.x;
		number--;
		if (position.x <= m_basePos.x - m_size.x)
		{
			//左端だった場合はそのまま
			position.x = m_basePos.x;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonUp))
	{
		//上にカーソルを動かす
		position.y += m_size.y;
		number -= m_width;
		if (position.y >= m_basePos.y + m_size.y)
		{
			//上端だった場合はそのまま
			position.y = m_basePos.y;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		//下にカーソルを動かす
		position.y -= m_size.y;
		number += m_width;
		if (position.y <= m_basePos.y - m_size.y * m_height)
		{
			//下端だった場合はそのまま
			position.y = m_basePos.y - m_size.y * (m_height - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	//座標を更新
	m_pointer.SetPosition(position);
	if (Pad().IsTriggerButton(enButtonA))
	{
		IInventoryItem* item = GetItemList().GetItem(m_pointerNum);
		if (item != nullptr)
		{
			const int PRICE_RATE = 5;
			int price = item->GetStatus().Itemprice / PRICE_RATE;
			GetPlayer().GainGold(price);
			GetItemList().Erase(m_pointerNum);
			const std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
			int idx = 0;
			for (auto& item : itemList)
			{
				//座標とサイズを決める
				CVector2 position = m_basePos;
				position.x += m_size.x * (idx % m_width);
				position.y -= m_size.y * (idx / m_width);
				item->GetSprite()->SetPosition(position);
				item->GetSprite()->SetSize(m_size);
				idx++;
			}
		}
	}
	if (Pad().IsTriggerButton(enButtonB))
	{
		Delete(this);
	}
	IInventoryItem* item = GetItemList().GetItem(m_pointerNum);

	if (item != nullptr)
	{
		m_choiceItemStatus = item->GetStatus();
		m_itemName.SetString(m_choiceItemStatus.ItemName);
	}
	wchar_t str[64];
	swprintf(str, L"%dG", GetPlayer().GetStatus().Gold);
	m_money.SetString(str);
}

void CItemShopSale::PostAfterDraw()
{
	m_backGround.Draw();
	m_headline.Draw();
	m_inventoryWindow.Draw();
	for (int i = 0; i < CItemList::m_itemLimit; i++)
	{
		m_itemFrame[i].Draw();
	}

	const std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
	for (auto& item : itemList)
	{
		item->Draw();
	}
	m_pointer.Draw();
	m_buttonBackground.Draw();
	m_itemWindow.Draw();
	m_itemName.Draw();
	m_money.Draw();
}