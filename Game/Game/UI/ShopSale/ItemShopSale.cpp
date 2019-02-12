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
	//�C���x���g���̕��ƍ�����������
	m_width = 5;
	m_height = CItemList::m_itemLimit / m_width;
	//���W�ƃT�C�Y��������
	m_basePos = { -450.0f, 190.0f };
	m_size = { 100.0f, 100.0f };
	//���ڂ�������
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/item.png");
	m_headline.Init(texture);
	m_headline.SetPosition({ -450.0f, 310.0f });
	m_headline.SetSize({ 300.0f, 75.0f });
	//�C���x���g���̔w�i��������
	texture = TextureResource().LoadTexture(L"Assets/sprite/BackGround.png");
	m_backGround.Init(texture);
	m_backGround.SetPosition({ 0.0f, 30.0f });
	m_backGround.SetSize({ 1250.0f, 650.0f });
	//�C���x���g���E�B���h�E��������
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_inventoryWindow.Init(texture);
	m_inventoryWindow.SetPosition({ -250.0f, -10.0f });
	m_inventoryWindow.SetSize({ 530.0f, 545.0f });
	//�J�[�\����������
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//�C���x���g���̘g��������
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
	//�{�^���\���̏�����
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonBackGround.png");
	m_buttonBackground.Init(texture);
	m_buttonBackground.SetSize({ 1200.0f, 40.0f });
	m_buttonBackground.SetPosition({ 0.0f, -325.0f });
	m_buttonBackground.SetAlpha(0.8f);

	const std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
	if (!itemList.empty())
	{
		//���X�g�ɃA�C�e��������
		int idx = 0;
		for (auto& item : itemList)
		{
			//���W�ƃT�C�Y�����߂�
			CVector2 position = m_basePos;
			position.x += m_size.x * (idx % m_width);
			position.y -= m_size.y * (idx / m_width);
			item->GetSprite()->SetPosition(position);
			item->GetSprite()->SetSize(m_size);
			idx++;
		}
	}
	//�A�C�e���E�B���h�E�̏�����
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_itemWindow.Init(texture);
	m_itemWindow.SetPosition({ 320.0f, 180.0f });
	m_itemWindow.SetSize({ 300.0f, 100.0f });
	//�A�C�e�����̏�����
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
		//�E�ɃJ�[�\���𓮂���
		position.x += m_size.x;
		number++;
		if (position.x >= m_basePos.x + m_size.x * m_width)
		{
			//�E�[�������ꍇ�͂��̂܂�
			position.x = m_basePos.x + m_size.x * (m_width - 1);
		}
		else
		{
			//��������J�[�\���őI��ł���ԍ����X�V
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		//���ɃJ�[�\���𓮂���
		position.x -= m_size.x;
		number--;
		if (position.x <= m_basePos.x - m_size.x)
		{
			//���[�������ꍇ�͂��̂܂�
			position.x = m_basePos.x;
		}
		else
		{
			//��������J�[�\���őI��ł���ԍ����X�V
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonUp))
	{
		//��ɃJ�[�\���𓮂���
		position.y += m_size.y;
		number -= m_width;
		if (position.y >= m_basePos.y + m_size.y)
		{
			//��[�������ꍇ�͂��̂܂�
			position.y = m_basePos.y;
		}
		else
		{
			//��������J�[�\���őI��ł���ԍ����X�V
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		//���ɃJ�[�\���𓮂���
		position.y -= m_size.y;
		number += m_width;
		if (position.y <= m_basePos.y - m_size.y * m_height)
		{
			//���[�������ꍇ�͂��̂܂�
			position.y = m_basePos.y - m_size.y * (m_height - 1);
		}
		else
		{
			//��������J�[�\���őI��ł���ԍ����X�V
			m_pointerNum = number;
		}
	}
	//���W���X�V
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
				//���W�ƃT�C�Y�����߂�
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