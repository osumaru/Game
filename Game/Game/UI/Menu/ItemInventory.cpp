#include "stdafx.h"
#include "ItemInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/InventoryItem/IInventoryItem.h"

std::list<std::unique_ptr<IInventoryItem>> CItemInventory::m_itemList;

CItemInventory::CItemInventory(){}

CItemInventory::~CItemInventory(){}

void CItemInventory::Init(CMenu* menu)
{
	m_menu = menu;
	//インベントリの幅と高さを初期化
	m_width = 5;
	m_height = m_itemLimit / m_width;
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
	for (int i = 0; i < m_itemLimit; i++)
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
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonA.png");
	m_buttonA.Init(texture);
	m_buttonA.SetSize({ 30.0f,30.0f });
	m_buttonA.SetPosition({ 200.0f, -325.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonB.png");
	m_buttonB.Init(texture);
	m_buttonB.SetSize({ 30.0f,30.0f });
	m_buttonB.SetPosition({ 330.0f, -325.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonY.png");
	m_buttonY.Init(texture);
	m_buttonY.SetSize({ 30.0f,30.0f });
	m_buttonY.SetPosition({ 460.0f, -325.0f });
	//ボタン文字の初期化
	texture = TextureResource().LoadTexture(L"Assets/sprite/use.png");
	m_buttonAMoji.Init(texture);
	m_buttonAMoji.SetPosition({ 240.0f, -325.0f });
	m_buttonAMoji.SetSize({ 40.0f,20.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/return.png");
	m_buttonBMoji.Init(texture);
	m_buttonBMoji.SetPosition({ 370.0f, -325.0f });
	m_buttonBMoji.SetSize({ 40.0f,20.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/erase.png");
	m_buttonYMoji.Init(texture);
	m_buttonYMoji.SetPosition({ 510.0f, -325.0f });
	m_buttonYMoji.SetSize({ 60.0f,20.0f });
	if (!m_itemList.empty()) 
	{
		//リストにアイテムがある
		int idx = 0;
		for (auto& item : m_itemList)
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

bool CItemInventory::Start()
{
	//メニューを動かさないようにする
	m_menu->SetIsActive(false);
	return true;
}

void CItemInventory::Update()
{
	//カーソル移動
	PointerMove();

	//アイテムの名前を設定する
	if (m_pointerNum < m_itemList.size() && !m_itemList.empty())
	{
		std::list<std::unique_ptr<IInventoryItem>>::iterator it;
		it = m_itemList.begin();
		for (int i = 0; i < m_pointerNum; i++)
		{
			it++;
		}
		m_itemName.SetString((*it)->GetItemName());
	}
	else 
	{
		m_itemName.SetString(L"");
	}

	if (Pad().IsTriggerButton(enButtonA)) 
	{
		//アイテムを使用する
		UseItem();
	}

	if (Pad().IsTriggerButton(enButtonY))
	{
		//アイテムを捨てる
		Erase();
	}

	if (Pad().IsTriggerButton(enButtonB))
	{
		//メニューに戻る
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CItemInventory::PostAfterDraw()
{
	m_backGround.Draw();
	m_headline.Draw();
	m_inventoryWindow.Draw();
	for (int i = 0; i < m_itemLimit; i++)
	{
		m_itemFrame[i].Draw();
	}
	for (auto& item : m_itemList)
	{
		item->Draw();
	}
	m_pointer.Draw();
	m_buttonBackground.Draw();
	m_buttonA.Draw();
	m_buttonB.Draw();
	m_buttonY.Draw();
	m_buttonAMoji.Draw();
	m_buttonBMoji.Draw();
	m_buttonYMoji.Draw();
	m_itemWindow.Draw();
	m_itemName.Draw();
}

void CItemInventory::PointerMove()
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
}

void CItemInventory::UseItem()
{
	//アイテムの数を取得
	size_t itemNum = m_itemList.size();
	if (m_pointerNum >= itemNum || m_itemList.empty())
	{
		return;
	}
	//選んだアイテムを使う
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	bool isUse = (*it)->Use();
	if (isUse) 
	{
		//使ったアイテムをリストから削除する
		m_itemList.erase(it);
	}
	int idx = 0;
	for (auto& item : m_itemList)
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

void CItemInventory::Erase()
{
	//アイテムの数を取得
	size_t itemNum = m_itemList.size();
	if (m_pointerNum >= itemNum || m_itemList.empty())
	{
		return;
	}
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	//リストから削除する
	m_itemList.erase(it);
	int idx = 0;
	for (auto& item : m_itemList)
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

void CItemInventory::AddItemList(std::unique_ptr<IInventoryItem> item)
{
	//アイテムリストに追加
	m_itemList.push_back(std::move(item));
}

bool CItemInventory::IsSpaceItemList()
{
	if (m_itemList.size() < m_itemLimit)
	{
		//リストに空きがある
		return true;
	}
	return false;
}
