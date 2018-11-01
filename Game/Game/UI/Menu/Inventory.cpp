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

	m_basePos = { -560.0f, 180.0f };
	m_size = { 150.0f, 150.0f };

	m_inventoryTexture.Load(L"Assets/sprite/Inventory.png");
	m_inventory.Init(&m_inventoryTexture);

	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);

	m_itemList = GetPlayer().GetItemList();
	m_inventoryWidth = 5;
	m_inventoryHeight = 0;
	if (!m_itemList.empty()) {
		int idx = 0;
		for (auto& item : m_itemList)
		{
			IItem::EnInventoryItemType itemType = item->GetItemType();
			if (itemType == IItem::Recovery) {
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/Recovery.png");
				m_recoveryItem[idx].Init(itemTexure);
				CVector2 position = m_basePos;
				position.x += m_size.x * (idx % m_inventoryWidth);
				position.y += m_size.y * idx * m_inventoryHeight;
				if (idx % m_inventoryWidth == m_inventoryWidth - 1)
				{
					m_inventoryHeight++;
				}
				m_recoveryItem[idx].SetPosition(position);
				m_recoveryItem[idx].SetSize(m_size);
			}
			idx++;
		}
	}
}

bool CInventory::Start()
{
	m_menu->SetIsActive(false);
	return true;
}

void CInventory::Update()
{
	int itemNum = m_itemList.size();
	int number = m_pointerNum;
	CVector2 position = m_pointer.GetPosition();
	if (Pad().IsTriggerButton(enButtonRight))
	{
		position.x += m_size.x;
		number++;
		if(position.x >= m_basePos.x + m_size.x * (m_inventoryWidth - 1))
		{
			position.x = m_basePos.x + m_size.x * (m_inventoryWidth - 1);
		}
		else 
		{
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLeft)) 
	{
		position.x -= m_size.x;
		number--;
		if (position.x <= m_basePos.x) 
		{
			position.x = m_basePos.x;
		}
		else 
		{
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonUp)) 
	{
		position.y += m_size.y;
		number -= m_inventoryWidth;
		if (position.y >= m_basePos.y) 
		{
			position.y = m_basePos.y;
		}
		else
		{
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonDown)) 
	{
		position.y -= m_size.y;
		number += m_inventoryWidth;
		if (position.y <= m_basePos.y - m_size.y * m_inventoryHeight)
		{
			position.y = m_basePos.y - m_size.y * m_inventoryHeight;
		}
		else 
		{
			m_pointerNum = number;
		}
	}
	m_pointer.SetPosition(position);

	//if ((m_pointerNum < itemNum) && Pad().IsTriggerButton(enButtonA))
	//{
	//	GetPlayer().UseItem(m_pointerNum);
	//	m_recoveryItem[m_pointerNum].SetIsDraw(false);
	//}

	if (Pad().IsTriggerButton(enButtonB)) {
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CInventory::AfterDraw()
{
	m_inventory.Draw();
	for (int i = 0; i < m_itemList.size(); i++) {
		m_recoveryItem[i].Draw();
	}
	m_pointer.Draw();
}
