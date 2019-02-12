#include "stdafx.h"
#include "EquipShopSale.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"
#include "../../Item/InventoryItem/IInventoryEquip.h"

CEquipShopSale::CEquipShopSale()
{
}

CEquipShopSale::~CEquipShopSale()
{
}

void CEquipShopSale::Init()
{
	m_money.Init(L"0G");
	m_money.SetPosition({ 300.0f, 200.0f });
	//�C���x���g���̕��ƍ�����������
	m_width = 5;
	m_height = CEquipList::m_equipLimit / m_width;
	//���W�ƃT�C�Y��������
	m_basePos = { -550.0f, 200.0f };
	m_baseSize = { 100.0f, 100.0f };
	//���ڂ�������
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/Weapon.png");
	m_headline.Init(texture);
	m_headline.SetPosition({ -450.0f, 310.0f });
	m_headline.SetSize({ 300.0f, 75.0f });
	//�C���x���g���̔w�i��������
	texture = TextureResource().LoadTexture(L"Assets/sprite/BackGround.png");
	m_background.Init(texture);
	m_background.SetPosition({ 0.0f, 30.0f });
	m_background.SetSize({ 1250.0f, 650.0f });
	//�C���x���g���E�B���h�E��������
	texture = TextureResource().LoadTexture(L"Assets/sprite/InventoryWindow.png");
	m_inventoryWindow.Init(texture);
	m_inventoryWindow.SetPosition({ -350.0f, -10.0f });
	m_inventoryWindow.SetSize({ 530.0f, 560.0f });
	//�C���x���g���̘g��������
	texture = TextureResource().LoadTexture(L"Assets/sprite/Frame.png");
	for (int i = 0; i < CEquipList::m_equipLimit; i++)
	{
		m_frame[i].Init(texture);
		m_frame[i].SetSize(m_baseSize);
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (i % m_width);
		position.y -= m_baseSize.y * (i / m_width);
		m_frame[i].SetPosition(position);
	}

	//�X�e�[�^�X�E�B���h�E�̔w�i��������
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");

	m_statusWindow.Init(texture);
	m_statusWindow.SetSize({ 340.0f, 450.0f });
	m_statusWindow.SetPosition({ 100.0f, 30.0f });
	//�J�[�\����������
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);


	//�������X�g�𐮗�����
	EquipListReset();
	//�X�e�[�^�X�\����������
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y - 70.0f };
	wchar_t fontMoji[256];
	wchar_t fontNum[256];
	for (int i = 0; i < CEquipInventory::enStatus_Num; i++)
	{
		switch (i)
		{
		case CEquipInventory::enStatus_Hp:
			swprintf(fontMoji, L"�ő�HP : ");
			swprintf(fontNum, L"%d", playerStatus.MaxHealth);
			break;
		case CEquipInventory::enStatus_Attack:
			swprintf(fontMoji, L"�U���� : ");
			swprintf(fontNum, L"%d", playerStatus.Strength);
			break;
		case CEquipInventory::enStatus_Defense:
			swprintf(fontMoji, L"�h��� : ");
			swprintf(fontNum, L"%d", playerStatus.Defense);
			break;
		}
		m_statusFont[i].Init(fontMoji);
		m_statusFont[i].SetPosition({
			fontPos.x + 30.0f,
			fontPos.y - m_baseSize.y * i
			});
		CVector2 fontSize = { 0.7f, 0.7f };
		m_statusFont[i].SetSize(fontSize);

		m_statusFontNum[i].Init(fontNum);
		m_statusFontNum[i].SetPosition({
			fontPos.x + 160.0f,
			fontPos.y - m_baseSize.y * i
			});
		m_statusFontNum[i].SetSize(fontSize);
	}
	//�����̖��O��������
	m_equipName.Init(L"");
	m_equipName.SetSize({ 0.7f,0.7f });
	m_equipName.SetPosition({
		m_statusWindow.GetPosition().x - 100.0f,
		fontPos.y + m_baseSize.y - 30.0f
		});


	m_equipSound[0].Init("Assets/sound/SystemSound/EquipOn.wav");
	m_equipSound[1].Init("Assets/sound/SystemSound/EquipOff.wav");
}
void CEquipShopSale::Update()
{
	//�J�[�\���ړ�
	PointerMove();

	if (Pad().IsTriggerButton(enButtonA))
	{
		
		//�A�C�e�����̂Ă�
		Sale();
	}

	if (Pad().IsTriggerButton(enButtonB))
	{
		Delete(this);
	}

	wchar_t str[64];
	swprintf(str, L"%dG", GetPlayer().GetStatus().Gold);
	m_money.SetString(str);
	IInventoryEquip* equip = GetEquipList().GetEquip(m_pointerNum);
	if(equip != nullptr)
	{
		m_equipName.SetString(equip->GetItemStatus().ItemName);
		wchar_t attackStr[16];
		swprintf(attackStr, L"%d", equip->GetEquipStatus().attack);
		m_statusFontNum[CEquipInventory::enStatus_Attack].SetString(attackStr);
	}
	else
	{
		m_equipName.SetString(L"");
	}
}

void CEquipShopSale::PostAfterDraw()
{
	m_background.Draw();
	m_headline.Draw();
	m_inventoryWindow.Draw();
	for (int i = 0; i < CEquipList::m_equipLimit; i++)
	{
		m_frame[i].Draw();
	}
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();
	for (auto& equip : equipList)
	{
		equip->Draw();
	}

	m_pointer.Draw();

	m_statusWindow.Draw();

	for (int i = 0; i < CEquipInventory::enStatus_Num; i++)
	{
		m_statusFont[i].Draw();
		m_statusFontNum[i].Draw();
	}
	m_equipName.Draw();
	m_money.Draw();
}

void CEquipShopSale::EquipListReset()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();
	if (equipList.empty())
	{
		//�����������Ȃ�
		return;
	}
	int idx = 0;
	for (auto& equip : equipList)
	{
		//���W�����߂�
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (idx % m_width);
		position.y -= m_baseSize.y * (idx / m_width);
		equip->GetSprite()->SetPosition(position);
		equip->GetSprite()->SetSize(m_baseSize);
		idx++;
	}
}

void CEquipShopSale::PointerMove()
{
	CVector2 position = m_pointer.GetPosition();
	int number = m_pointerNum;
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//�E�ɃJ�[�\���𓮂���
		position.x += m_baseSize.x;
		number++;
		if (position.x >= m_basePos.x + m_baseSize.x * m_width)
		{
			//�E�[�������ꍇ�͂��̂܂�
			position.x = m_basePos.x + m_baseSize.x * (m_width - 1);
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
		position.x -= m_baseSize.x;
		number--;
		if (position.x <= m_basePos.x - m_baseSize.x)
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
		position.y += m_baseSize.y;
		number -= m_width;
		if (position.y >= m_basePos.y + m_baseSize.y)
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
		position.y -= m_baseSize.y;
		number += m_width;
		if (position.y <= m_basePos.y - m_baseSize.y * m_height)
		{
			//���[�������ꍇ�͂��̂܂�
			position.y = m_basePos.y - m_baseSize.y * (m_height - 1);
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


void CEquipShopSale::Sale()
{
	std::list<std::unique_ptr<IInventoryEquip>>& equipList = GetEquipList().GetBody();

	IInventoryEquip* equip = GetEquipList().GetEquip(m_pointerNum);
	if (equip != nullptr)
	{
		const int PRICE_RATE = 5;
		int gold = equip->GetItemStatus().Itemprice / PRICE_RATE;
		GetPlayer().GainGold(gold);
		GetEquipList().Erase(m_pointerNum);
		//�������X�g�𐮗�����
		EquipListReset();
		//�������̂Ă�Ƃ��̉���炷����
		if (m_equipSound[1].IsPlay())
		{
			m_equipSound[1].Stop();
		}
		m_equipSound[1].Play(false, true);
	}
	
}
