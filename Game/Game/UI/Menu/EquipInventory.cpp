#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"

CEquipInventory::CEquipInventory(){}

CEquipInventory::~CEquipInventory(){}

void CEquipInventory::Init(CMenu * menu)
{
	m_menu = menu;
	//�C���x���g���̕��ƍ�����������
	m_width = 5;
	m_height = 3;
	//���W�ƃT�C�Y��������
	m_basePos = { -560.0f, 180.0f };
	m_baseSize = { 100.0f, 100.0f };
	//�C���x���g���̔w�i��������
	m_backGroundTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(&m_backGroundTexture);
	m_statusWindowTexture.Load(L"Assets/sprite/statusWindow.png");
	m_statusWindow.Init(&m_statusWindowTexture);
	m_statusWindow.SetSize({ 320.0f, 450.0f });
	m_statusWindow.SetAlpha(0.3f);
	m_rightTexture.Load(L"Assets/sprite/right.png");
	m_right.Init(&m_rightTexture);
	m_right.SetSize(m_baseSize);
	//�J�[�\����������
	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);
	//�������X�g���擾
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//���X�g�ɃA�C�e��������
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//�A�C�e���̎�ނ��擾
			EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == enWeaponSword)
			{
				//��
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == enWeaponLongSword)
			{
				//�匕
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == enWeaponArrow)
			{
				//�|
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == enWeaponTwinSword)
			{
				//�o��
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].Init(itemTexure);
			}
			//���W�ƃT�C�Y�����߂�
			CVector2 position = m_basePos;
			position.x += m_baseSize.x * (idx % m_width);
			position.y -= m_baseSize.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//�C���x���g���̕��𒴂�����s��������
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_baseSize);
			idx++;
		}
	}
	m_pointer.SetSize(m_baseSize);
	//�������X�g�𐮗�����
	EquipListReset(true);
	//�X�e�[�^�X�\����������
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y };
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
			m_statusFont[j][i].SetPosition({
					fontPos.x + (m_right.GetSize().x + m_statusWindow.GetSize().x) * j,
					fontPos.y - m_baseSize.y * i
			});
			CVector2 fontSize = { 0.7f, 0.7f };
			m_statusFont[j][i].SetSize(fontSize);
		}
	}
	CVector2 statusWindowPos = { m_basePos.x + m_baseSize.x * m_width, m_basePos.y };
	statusWindowPos.x += m_statusWindow.GetSize().x / 2.0f - 30.0f;
	statusWindowPos.y -= m_baseSize.y;
	m_statusWindow.SetPosition(statusWindowPos);
	CVector2 rightPos = statusWindowPos;
	rightPos.x += m_statusWindow.GetSize().x / 2.0f + m_right.GetSize().x / 2.0f;
	m_right.SetPosition(rightPos);
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
	m_statusWindow.Draw();
	m_right.Draw();
	for (int j = 0; j < enFont_StatusNum; j++) {
		for (int i = 0; i < enStatus_Num; i++) {
			m_statusFont[j][i].Draw();
		}
	}
}

void CEquipInventory::EquipListReset(bool isInit)
{
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	if (m_equipList.empty()) 
	{
		//�����������Ȃ�
		return;
	}
	int idx = 0;
	for (auto& equip : m_equipList)
	{
		//�����̎�ނ��擾
		EnPlayerWeapon weaponNum = equip.weaponNum;
		CTexture* equipTexture = nullptr;
		if (weaponNum == enWeaponSword)
		{
			//��
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
		}
		else if (weaponNum == enWeaponLongSword)
		{
			//�匕
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
		}
		else if (weaponNum == enWeaponArrow)
		{
			//�|
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
		}
		else if (weaponNum == enWeaponTwinSword)
		{
			//�o��
			equipTexture = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
		}
		if (isInit) {
			//����������
			m_equip[idx].Init(equipTexture);
		}
		else {
			//�e�N�X�`����ݒ肷��
			m_equip[idx].SetTexture(equipTexture);
		}
		//���W�ƃT�C�Y�����߂�
		CVector2 position = m_basePos;
		position.x += m_baseSize.x * (idx % m_width);
		position.y -= m_baseSize.y * (idx / m_width);
		m_equip[idx].SetPosition(position);
		m_equip[idx].SetSize(m_baseSize);
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

void CEquipInventory::Equip()
{
	//�����̐����擾
	size_t equipNum = m_equipList.size();
	if (m_pointerNum >= equipNum || !Pad().IsTriggerButton(enButtonA)) {
		return;
	}
	//�J�[�\���őI��ł��鑕��������
	GetPlayer().GetWeaponManager().ChangeEquip(m_pointerNum);
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//���X�g�ɃA�C�e��������
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//�A�C�e���̎�ނ��擾
			EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == enWeaponSword)
			{
				//��
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == enWeaponLongSword)
			{
				//�匕
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == enWeaponArrow)
			{
				//�|
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == enWeaponTwinSword)
			{
				//�o��
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			//���W�ƃT�C�Y�����߂�
			CVector2 position = m_basePos;
			position.x += m_baseSize.x * (idx % m_width);
			position.y -= m_baseSize.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//�C���x���g���̕��𒴂�����s��������
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_baseSize);
			idx++;
		}
	}
	GetPlayer().GetWeaponManager().ChangeEquip(m_pointerNum);
	//�������X�g�𐮗�����
	EquipListReset(false);
}

void CEquipInventory::CalucStatus()
{
	//�v���C���[�̃X�e�[�^�X���擾
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	//�����̐����擾
	size_t equipNum = m_equipList.size();
	SWeaponStatus weaponStatus;
	if (m_pointerNum < equipNum) {
		//�������Ă��鑕����I��ł���ꍇ�͂��̑����̃X�e�[�^�X���擾
		std::list<SWeaponStatus>::iterator it;
		it = m_equipList.begin();
		for (int i = 0; i < m_pointerNum; i++)
		{
			it++;
		}
		weaponStatus = (*it);
	}

	//�����ύX�����ꍇ�̃X�e�[�^�X���v�Z����
	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		SWeaponStatus equipStatus;
		if (weaponStatus.weaponNum != EnPlayerWeapon::enInvalid)
		{
			//���݂̑����̃X�e�[�^�X���擾
			equipStatus = GetPlayer().GetWeaponManager().GetWeaponStatus(weaponStatus.weaponNum);
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
}
