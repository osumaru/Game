#include "stdafx.h"
#include "ItemInventory.h"
#include "Menu.h"
#include "../../Item/InventoryItem/IInventoryItem.h"
#include "../../Item/ItemList.h"
#include "../../Player/Player.h"

//std::list<std::unique_ptr<IInventoryItem>> CItemInventory::m_itemList;

CItemInventory::CItemInventory(){}

CItemInventory::~CItemInventory(){}

void CItemInventory::Init(CMenu* menu)
{
	m_menu = menu;
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
	//�{�^�������̏�����
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
			GetItemList().SetSpritePos(idx, position);
			GetItemList().SetSpriteSize(idx, m_size);
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
	const std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
	if (m_pointerNum < itemList.size() && !itemList.empty())
	{
		std::list<std::unique_ptr<IInventoryItem>>::const_iterator it;
		it = itemList.begin();
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

	if (Pad().IsTriggerButton(enButtonY))
	{
		//�A�C�e�����̂Ă�
		Erase();
	}

	if (Pad().IsTriggerButton(enButtonB))
	{
		//���j���[�ɖ߂�
		m_menu->SetIsActive(true);
		m_menu->ReleaseInventory();
		//�߂�{�^���̉���炷
		CSoundSource* returnSound = New<CSoundSource>(0);
		returnSound->Init("Assets/sound/SystemSound/MenuOpen.wav");
		returnSound->Play(false);
		Delete(this);
	}
}

void CItemInventory::PostAfterDraw()
{
	m_backGround.Draw();
	m_headline.Draw();
	m_inventoryWindow.Draw();
	for (int i = 0; i < CItemList::m_itemLimit; i++)
	{
		m_itemFrame[i].Draw();
	}
	GetItemList().Draw();
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
	bool isCursorMove = false;
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
			isCursorMove = true;
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
			isCursorMove = true;
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
			isCursorMove = true;
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
			isCursorMove = true;
		}
	}
	//���W���X�V
	m_pointer.SetPosition(position);
	if (isCursorMove)
	{
		//�I������炷
		/*CSoundSource* selectSound = New<CSoundSource>(0);
		selectSound->Init("Assets/sound/SystemSound/EquipOn.wav");
		selectSound->Play(false);*/
	}
}

void CItemInventory::UseItem()
{
	//�A�C�e���̐����擾
	std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
	GetItemList().Use(m_pointerNum);
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

void CItemInventory::Erase()
{
	const std::list<std::unique_ptr<IInventoryItem>>& itemList = GetItemList().GetBody();
	GetItemList().Erase(m_pointerNum);
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
