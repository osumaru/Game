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
	m_height = 3;
	//座標とサイズを初期化
	m_basePos = { -560.0f, 180.0f };
	m_size = { 150.0f, 150.0f };
	//インベントリの背景を初期化
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(texture);
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
	m_itemName.Init(L"");
	m_itemName.SetSize({ 0.7f,0.7f });
	m_itemName.SetPosition({ 320.0f, 180.0f });
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

	if (Pad().IsTriggerButton(enButtonB))
	{
		//メニューに戻る
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CItemInventory::AfterDraw()
{
	m_backGround.Draw();
	for (int i = 0; i < m_itemLimit; i++)
	{
		m_itemFrame[i].Draw();
	}
	for (auto& item : m_itemList)
	{
		item->Draw();
	}
	m_pointer.Draw();
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

void CItemInventory::AddItemList(std::unique_ptr<IInventoryItem> item)
{
	if (m_itemList.size() < m_itemLimit)
	{
		//所持上限を超えていなければアイテムリストに追加
		m_itemList.push_back(std::move(item));
	}
}
