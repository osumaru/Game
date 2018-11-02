#include "stdafx.h"
#include "Inventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Itam/IItem.h"

CInventory::CInventory(){}

CInventory::~CInventory(){}

void CInventory::Init(CMenu* menu)
{
	m_menu = menu;
	//座標とサイズを初期化
	m_basePos = { -560.0f, 180.0f };
	m_size = { 150.0f, 150.0f };
	//インベントリの背景を初期化
	m_inventoryTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_inventory.Init(&m_inventoryTexture);
	//カーソルを初期化
	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//アイテムリストを取得
	m_itemList = GetPlayer().GetItemList();
	m_inventoryWidth = 5;
	m_inventoryHeight = 1;
	if (!m_itemList.empty()) {
		//リストにアイテムがある
		int idx = 0;
		for (auto& item : m_itemList)
		{
			//アイテムの種類を取得
			IItem::EnInventoryItemType itemType = item->GetItemType();
			if (itemType == IItem::Recovery) {		//回復アイテムだった場合
				//回復アイテムの初期化
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/Recovery.png");
				m_item[idx].Init(itemTexure);
			}
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_size.x * (idx % m_inventoryWidth);
			position.y -= m_size.y * (idx / m_inventoryWidth);
			if (idx != 0 && idx % m_inventoryWidth == 0)
			{
				//インベントリの幅を超えたら行を下げる
				m_inventoryHeight++;
			}
			m_item[idx].SetPosition(position);
			m_item[idx].SetSize(m_size);
			idx++;
		}
	}
}

bool CInventory::Start()
{
	//メニューを動かさないようにする
	m_menu->SetIsActive(false);
	return true;
}

void CInventory::Update()
{
	//アイテムの数を取得
	int itemNum = m_itemList.size();
	int number = m_pointerNum;
	CVector2 position = m_pointer.GetPosition();
	float offset = m_size.x / 2.0f;
	if (Pad().IsTriggerButton(enButtonRight))	
	{
		//右にカーソルを動かす
		position.x += m_size.x;
		number++;
		if(position.x > m_basePos.x + m_size.x * (m_inventoryWidth - 1) + offset)
		{
			//右端だった場合はそのまま
			position.x = m_basePos.x + m_size.x * (m_inventoryWidth - 1);
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
		if (position.x < m_basePos.x - offset) 
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
		number -= m_inventoryWidth;
		if (position.y > m_basePos.y + offset) 
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
		number += m_inventoryWidth;
		if (position.y < m_basePos.y - m_size.y * (m_inventoryHeight - 1) - offset)
		{
			//下端だった場合はそのまま
			position.y = m_basePos.y - m_size.y * (m_inventoryHeight - 1);
		}
		else 
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	//座標を更新
	m_pointer.SetPosition(position);

	if (m_pointerNum < itemNum && Pad().IsTriggerButton(enButtonA))
	{
		//カーソルで選んでいるアイテムを使う
		GetPlayer().UseItem(m_pointerNum);
		//空いたスペースを詰める
		m_itemList = GetPlayer().GetItemList();
		m_inventoryWidth = 5;
		m_inventoryHeight = 1;
		if (!m_itemList.empty()) {
			//リストにアイテムがある
			int idx = 0;
			for (auto& item : m_itemList)
			{
				//座標とサイズを決める
				CVector2 position = m_basePos;
				position.x += m_size.x * (idx % m_inventoryWidth);
				position.y -= m_size.y * (idx / m_inventoryWidth);
				if (idx != 0 && idx % m_inventoryWidth == 0)
				{
					//インベントリの幅を超えたら行を下げる
					m_inventoryHeight++;
				}
				m_item[idx].SetPosition(position);
				m_item[idx].SetSize(m_size);
				idx++;
			}
		}
	}

	if (Pad().IsTriggerButton(enButtonB)) {
		//メニューに戻る
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CInventory::AfterDraw()
{
	m_inventory.Draw();
	for (int i = 0; i < m_itemList.size(); i++) {
		m_item[i].Draw();
	}
	m_pointer.Draw();
}
