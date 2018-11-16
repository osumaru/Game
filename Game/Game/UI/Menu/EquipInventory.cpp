#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"

CEquipInventory::CEquipInventory(){}

CEquipInventory::~CEquipInventory(){}

void CEquipInventory::Init(CMenu * menu)
{
	m_menu = menu;
	//���W�ƃT�C�Y��������
	m_basePos = { -560.0f, 180.0f };
	m_size = { 100.0f, 100.0f };
	//�C���x���g���̔w�i��������
	m_backGroundTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(&m_backGroundTexture);
	//�J�[�\����������
	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//�������X�g���擾
	m_equipList = GetPlayer().GetEquipList();
	m_width = 5;
	m_height = 1;
	//�������X�g�𐮗�����
	EquipListReset(true);
	//�X�e�[�^�X�\����������
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_size.x * m_width, m_basePos.y + m_size.y };
	wchar_t font[256];
	for (int j = 0; j < enFont_StatusNum; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			switch (i)
			{
			case enStatus_Hp:
				swprintf(font, L"�ő�HP : %d", playerStatus.MaxHealth);
				break;
			case enStatus_Attack:
				swprintf(font, L"�U���� : %d", playerStatus.Strength);
				break;
			case enStatus_Defense:
				swprintf(font, L"�h��� : %d", playerStatus.Defense);
				break;
			}
			m_statusFont[j][i].Init(font);
			m_statusFont[j][i].SetPosition({ fontPos.x + 320.0f * j, fontPos.y - m_size.y * i });
		}
	}
}

bool CEquipInventory::Start()
{
	m_menu->SetIsActive(false);
	return true;
}

void CEquipInventory::Update()
{
	//�J�[�\���ړ�
	PointerMove();

	//��������
	Equip();

	//�X�e�[�^�X�v�Z
	CalucStatus();

	if (Pad().IsTriggerButton(enButtonB)) {
		//���j���[�ɖ߂�
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CEquipInventory::AfterDraw()
{
	m_backGround.Draw();
	for (int i = 0; i < m_equipList.size(); i++) {
		m_equip[i].Draw();
	}
	m_pointer.Draw();
	for (int j = 0; j < enFont_StatusNum; j++) {
		for (int i = 0; i < enStatus_Num; i++) {
			m_statusFont[j][i].Draw();
		}
	}
}

void CEquipInventory::EquipListReset(bool isInit)
{
	if (m_equipList.empty()) 
	{
		//�����������Ȃ�
		return;
	}
	int idx = 0;
	for (auto& equip : m_equipList)
	{
		//�����̎�ނ��擾
		CWeapon::EnPlayerWeapon weaponNum = equip.weaponNum;
		CTexture* equipTexture = nullptr;
		if (weaponNum == CWeapon::enSword)
		{
			//��
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
		}
		else if (weaponNum == CWeapon::enLongSword)
		{
			//�匕
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
		}
		else if (weaponNum == CWeapon::enArrow)
		{
			//�|
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
		}
		else if (weaponNum == CWeapon::enTwinSword)
		{
			//�o��
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
		}
		if (isInit) {
			m_equip[idx].Init(equipTexture);
		}
		else {
			m_equip[idx].SetTexture(equipTexture);
		}
		//���W�ƃT�C�Y�����߂�
		CVector2 position = m_basePos;
		position.x += m_size.x * (idx % m_width);
		position.y -= m_size.y * (idx / m_width);
		if (idx != 0 && idx % m_width == 0)
		{
			//�C���x���g���̕��𒴂�����s��������
			m_height++;
		}
		m_equip[idx].SetPosition(position);
		m_equip[idx].SetSize(m_size);
		idx++;
	}
}

void CEquipInventory::PointerMove()
{
	CVector2 position = m_pointer.GetPosition();
	int number = m_pointerNum;
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

void CEquipInventory::Equip()
{
	//�����̐����擾
	size_t equipNum = m_equipList.size();
	if (m_pointerNum >= equipNum || !Pad().IsTriggerButton(enButtonA)) {
		return;
	}
	//�J�[�\���őI��ł��鑕��������
	GetPlayer().ChangeEquip(m_pointerNum);
	m_equipList = GetPlayer().GetEquipList();
	m_width = 5;
	m_height = 1;
	//�������X�g�𐮗�����
	EquipListReset(false);
}

void CEquipInventory::CalucStatus()
{
	//�v���C���[�̃X�e�[�^�X���擾
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	//�����̐����擾
	size_t equipNum = m_equipList.size();
	CWeapon::SWeaponStatus weaponStatus;
	if (m_pointerNum < equipNum) {
		//�������Ă��鑕����I��ł���ꍇ�͂��̑����̃X�e�[�^�X���擾
		std::list<CWeapon::SWeaponStatus>::iterator it;
		it = m_equipList.begin();
		for (int i = 0; i < m_pointerNum; i++)
		{
			it++;
		}
		weaponStatus = (*it);
	}

	CWeapon::SWeaponStatus equipStatus;
	if (weaponStatus.weaponNum != CWeapon::EnPlayerWeapon::enInvalid)
	{
		//���݂̑����̃X�e�[�^�X���擾
		equipStatus = GetPlayer().GetWeaponStatus(weaponStatus.weaponNum);
	}

	//�����ύX�����ꍇ�̃X�e�[�^�X���v�Z����
	wchar_t font[256];
	for (int j = 0; j < enFont_StatusNum; j++) {
		if (j == enFont_ChangeStatus)
		{
			equipStatus = weaponStatus;
		}
		for (int i = 0; i < enStatus_Num; i++)
		{
			int statusNum = 0;
			switch (i)
			{
			case enStatus_Hp:
				statusNum = playerStatus.MaxHealth;
				swprintf(font, L"�ő�HP : %d", statusNum);
				break;
			case enStatus_Attack:
				statusNum = equipStatus.attack + playerStatus.Strength;
				swprintf(font, L"�U���� : %d", statusNum);
				break;
			case enStatus_Defense:
				statusNum = equipStatus.diffence + playerStatus.Defense;
				swprintf(font, L"�h��� : %d", statusNum);
				break;
			}
			m_statusFont[j][i].SetString(font);
		}
	}
}
