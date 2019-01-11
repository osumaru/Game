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
	//�C���x���g���̕��ƍ�����������
	m_width = 5;
	m_height = 3;
	//���W�ƃT�C�Y��������
	m_basePos = { -560.0f, 180.0f };
	m_size = { 150.0f, 150.0f };
	//�C���x���g���̔w�i��������
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(texture);
	//�J�[�\����������
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//�C���x���g���̘g��������
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
		//���X�g�ɃA�C�e��������
		int idx = 0;
		for (auto& item : m_itemList)
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
	m_itemName.Init(L"");
	m_itemName.SetSize({ 0.7f,0.7f });
	m_itemName.SetPosition({ 320.0f, 180.0f });
}

bool CItemInventory::Start()
{
	//���j���[�𓮂����Ȃ��悤�ɂ���
	m_menu->SetIsActive(false);
	return true;
}

void CItemInventory::Update()
{
	//�J�[�\���ړ�
	PointerMove();

	//�A�C�e���̖��O��ݒ肷��
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
		//�A�C�e�����g�p����
		UseItem();
	}

	if (Pad().IsTriggerButton(enButtonB))
	{
		//���j���[�ɖ߂�
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
}

void CItemInventory::UseItem()
{
	//�A�C�e���̐����擾
	size_t itemNum = m_itemList.size();
	if (m_pointerNum >= itemNum || m_itemList.empty())
	{
		return;
	}
	//�I�񂾃A�C�e�����g��
	std::list<std::unique_ptr<IInventoryItem>>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	bool isUse = (*it)->Use();
	if (isUse) 
	{
		//�g�����A�C�e�������X�g����폜����
		m_itemList.erase(it);
	}
	int idx = 0;
	for (auto& item : m_itemList)
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

void CItemInventory::AddItemList(std::unique_ptr<IInventoryItem> item)
{
	if (m_itemList.size() < m_itemLimit)
	{
		//��������𒴂��Ă��Ȃ���΃A�C�e�����X�g�ɒǉ�
		m_itemList.push_back(std::move(item));
	}
}
