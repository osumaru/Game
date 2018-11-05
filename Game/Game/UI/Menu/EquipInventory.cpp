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
	m_size = { 150.0f, 150.0f };
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
	if (!m_equipList.empty()) {
		//���X�g�ɃA�C�e��������
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//�A�C�e���̎�ނ��擾
			CWeapon::EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == CWeapon::enSword)
			{
				//��
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeapon::enLongSword)
			{
				//�匕
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeapon::enArrow)
			{
				//�|
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeapon::enTwinSword)
			{
				//�o��
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].Init(itemTexure);
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

}

bool CEquipInventory::Start()
{
	m_menu->SetIsActive(false);
	return true;
}

void CEquipInventory::Update()
{
	//�����̐����擾
	size_t equipNum = m_equipList.size();
	int number = m_pointerNum;
	CVector2 position = m_pointer.GetPosition();
	float offset = m_size.x / 2.0f;
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//�E�ɃJ�[�\���𓮂���
		position.x += m_size.x;
		number++;
		if (position.x > m_basePos.x + m_size.x * (m_width - 1) + offset)
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
		if (position.x < m_basePos.x - offset)
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
		if (position.y > m_basePos.y + offset)
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
		if (position.y < m_basePos.y - m_size.y * (m_height - 1) - offset)
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

	if (m_pointerNum < equipNum && Pad().IsTriggerButton(enButtonA))
	{
		//�J�[�\���őI��ł��鑕��������
		GetPlayer().ChangeEquip(m_pointerNum);
		m_equipList = GetPlayer().GetEquipList();
		m_width = 5;
		m_height = 1;
		if (!m_equipList.empty()) {
			//���X�g�ɃA�C�e��������
			int idx = 0;
			for (auto& equip : m_equipList)
			{
				//�A�C�e���̎�ނ��擾
				CWeapon::EnPlayerWeapon weaponNum = equip.weaponNum;
				if (weaponNum == CWeapon::enSword)
				{
					//��
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				else if (weaponNum == CWeapon::enLongSword)
				{
					//�匕
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				else if (weaponNum == CWeapon::enArrow)
				{
					//�|
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
					m_equip[idx].SetTexture(itemTexure);
				}
				else if (weaponNum == CWeapon::enTwinSword)
				{
					//�o��
					CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
					m_equip[idx].SetTexture(itemTexure);
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
	}

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
}
