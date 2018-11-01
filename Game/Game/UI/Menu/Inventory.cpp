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

	CVector2 basePos = { -560.0f, 180.0f };
	CVector2 size = { 150.0f, 150.0f };

	m_inventoryTexture.Load(L"Assets/sprite/Inventory.png");
	m_inventory.Init(&m_inventoryTexture);

	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(basePos);
	m_pointer.SetSize(size);

	m_itemList = GetPlayer().GetItemList();
	if (!m_itemList.empty()) {
		int idx = 0;
		int inventoryWidth = 5;
		int inventoryHeight = 0;
		for (auto& item : m_itemList)
		{
			IItem::EnInventoryItemType itemType = item->GetItemType();
			if (itemType == IItem::Recovery) {
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/Recovery.png");
				m_recoveryItem[idx].Init(itemTexure);
				CVector2 position = basePos;
				position.x += size.x * (idx % inventoryWidth);
				position.y += size.y * idx * inventoryHeight;
				if (idx % inventoryWidth == inventoryWidth - 1)
				{
					inventoryHeight++;
				}
				m_recoveryItem[idx].SetPosition(position);
				m_recoveryItem[idx].SetSize(size);
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
