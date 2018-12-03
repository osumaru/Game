#include "stdafx.h"
#include "EquipInventory.h"
#include "Menu.h"
#include "../../Player/Player.h"
#include "../../Item/IItem.h"
#include "../../Player/Weapon/WeaponManager.h"

std::list<SWeaponStatus> CEquipInventory::m_equipList;

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
	CTexture* texture = TextureResource().LoadTexture(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_background.Init(texture);
	//A�{�^����B�{�^���\���̏�����
	texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
	m_buttonBackground.Init(texture);
	m_buttonBackground.SetSize({ 1280.0f, 60.0f });
	m_buttonBackground.SetPosition({ 0.0f, -330.0f });
	m_buttonBackground.SetAlpha(0.3f);
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonA.png");
	m_buttonA.Init(texture);
	m_buttonA.SetSize({ 35.0f,35.0f });
	m_buttonA.SetPosition({ 200.0f, -330.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonB.png");
	m_buttonB.Init(texture);
	m_buttonB.SetSize({ 35.0f,35.0f });
	m_buttonB.SetPosition({ 325.0f, -330.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/ButtonY.png");
	m_buttonY.Init(texture);
	m_buttonY.SetSize({ 35.0f,35.0f });
	m_buttonY.SetPosition({ 450.0f, -330.0f });
	//�{�^���t�H���g�̏�����
	m_buttonAFont.Init(L"��������");
	m_buttonAFont.SetSize({ 0.5f, 0.5f });
	m_buttonAFont.SetPosition({ 212.5f, -319.0f });
	m_buttonBFont.Init(L"�߂�");
	m_buttonBFont.SetSize({ 0.5f, 0.5f });
	m_buttonBFont.SetPosition({ 342.5f, -319.0f });
	m_buttonYFont.Init(L"�̂Ă�");
	m_buttonYFont.SetSize({ 0.5f, 0.5f });
	m_buttonYFont.SetPosition({ 472.5f, -319.0f });
	//�X�e�[�^�X�E�B���h�E�̔w�i��������
	for (int i = 0; i < enFont_StatusNum; i++) 
	{
		texture = TextureResource().LoadTexture(L"Assets/sprite/statusWindow.png");
		m_statusWindow[i].Init(texture);
		m_statusWindow[i].SetSize({ 320.0f, 450.0f });
		m_statusWindow[i].SetAlpha(0.3f);
	}
	m_statusWindow[enFont_CurrentStatus].SetPosition({ 70.0f, 80.0f });
	m_statusWindow[enFont_ChangeStatus].SetPosition({ 470.0f, 80.0f });
	//�E���̏�����
	texture = TextureResource().LoadTexture(L"Assets/sprite/right.png");
	m_right.Init(texture);
	m_right.SetSize({ 80.0f, 80.0f });
	m_right.SetPosition({ 270.0f, 80.0f });
	//�J�[�\����������
	texture = TextureResource().LoadTexture(L"Assets/sprite/Pointer.png");
	m_pointer.Init(texture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_baseSize);
	//��������̃A�C�R����������
	texture = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
	m_equipWeapon[enWeaponSword].Init(texture);
	m_equipWeapon[enWeaponSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponSword].SetPosition({ -360.0f, -120.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
	m_equipWeapon[enWeaponLongSword].Init(texture);
	m_equipWeapon[enWeaponLongSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponLongSword].SetPosition({ -290.0f, -190.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
	m_equipWeapon[enWeaponArrow].Init(texture);
	m_equipWeapon[enWeaponArrow].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponArrow].SetPosition({ -360.0f, -260.0f });
	texture = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
	m_equipWeapon[enWeaponTwinSword].Init(texture);
	m_equipWeapon[enWeaponTwinSword].SetSize({ 65.0f,65.0f });
	m_equipWeapon[enWeaponTwinSword].SetPosition({ -430.0f, -190.0f });
	for (int i = 0; i < enWeaponNum; i++)
	{
		IWeapon* weapon = GetPlayer().GetWeaponManager().GetWeapon((EnPlayerWeapon)i);
		if (weapon->GetWeaponStatus().weaponNum == enInvalid) 
		{
			//�������Ȃ���Ε`�悵�Ȃ�
			m_equipWeapon[i].SetIsDraw(false);
		}
		//��������A�C�R���̘g�̏�����
		texture = TextureResource().LoadTexture(L"Assets/sprite/EquipFrame.png");
		m_equipFrame[i].Init(texture);
		m_equipFrame[i].SetSize({ 70.0f,70.0f });
		m_equipFrame[i].SetPosition(m_equipWeapon[i].GetPosition());
	}
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
					fontPos.x + (m_right.GetSize().x + m_statusWindow[enFont_CurrentStatus].GetSize().x) * j,
					fontPos.y - m_baseSize.y * i
			});
			CVector2 fontSize = { 0.7f, 0.7f };
			m_statusFont[j][i].SetSize(fontSize);
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

	if (Pad().IsTriggerButton(enButtonA)) 
	{
		//��������
		Equip();
	}

	if (Pad().IsTriggerButton(enButtonY))
	{
		//�A�C�e�����̂Ă�
		Erase();
	}

	//�X�e�[�^�X�v�Z
	CalucStatus();

	if (Pad().IsTriggerButton(enButtonB)) 
	{
		//���j���[�ɖ߂�
		m_menu->SetIsActive(true);
		Delete(this);
	}
}

void CEquipInventory::AfterDraw()
{
	m_background.Draw();
	for (int i = 0; i < m_equipList.size(); i++)
	{
		m_equip[i].Draw();
	}
	for (int i = 0; i < enWeaponNum; i++)
	{
		m_equipFrame[i].Draw();
		m_equipWeapon[i].Draw();
	}
	m_pointer.Draw();
	for (int i = 0; i < enFont_StatusNum; i++)
	{
		m_statusWindow[i].Draw();
	}
	m_right.Draw();
	m_buttonBackground.Draw();
	m_buttonA.Draw();
	m_buttonB.Draw();
	m_buttonY.Draw();
	for (int j = 0; j < enFont_StatusNum; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			m_statusFont[j][i].Draw();
		}
	}
	m_buttonAFont.Draw();
	m_buttonBFont.Draw();
	m_buttonYFont.Draw();
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
	if (m_pointerNum >= equipNum || m_equipList.empty()) {
		//�I�񂾏ꏊ�̑��������X�g�̒��ɂȂ����̓��X�g����ɂȂ��Ă���
		return;
	}
	//�I�񂾕���̃A�C�R����`�悳����
	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	EnPlayerWeapon weaponNumber = (*it).weaponNum;
	m_equipWeapon[weaponNumber].SetIsDraw(true);
	//�I�񂾑����ƌ��݂̑�������������
	IWeapon* weapon = GetPlayer().GetWeaponManager().GetWeapon(weaponNumber);
	if (weapon->GetWeaponStatus().weaponNum == enInvalid)
	{
		//�����������Ă��Ȃ�
		weapon->SetWeaponStatus(*it);
		m_equipList.erase(it);
	}
	else
	{
		//��������������
		SWeaponStatus equipWeapon = weapon->GetWeaponStatus();
		weapon->SetWeaponStatus(*it);
		(*it) = equipWeapon;
	}
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

	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	SWeaponStatus equipStatus;
	if (weaponStatus.weaponNum != EnPlayerWeapon::enInvalid)
	{
		//���݂̑����̃X�e�[�^�X���擾
		equipStatus = GetPlayer().GetWeaponManager().GetWeaponStatus(weaponStatus.weaponNum);
	}

	//�����ύX�����ꍇ�̃X�e�[�^�X���v�Z����
	wchar_t font[256];
	for (int j = 0; j < enFont_StatusNum; j++) 
	{
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

void CEquipInventory::Erase()
{
	//�����̐����擾
	size_t equipNum = m_equipList.size();
	if (m_pointerNum >= equipNum || m_equipList.empty()) {
		//�I�񂾏ꏊ�̑��������X�g�̒��ɂȂ����̓��X�g����ɂȂ��Ă���
		return;
	}
	//�I�񂾑������̂Ă�
	std::list<SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	m_equipList.erase(it);
	//�������X�g�𐮗�����
	EquipListReset(false);
}

void CEquipInventory::AddEquipList(SWeaponStatus& weaponStatus)
{
	if (m_equipList.size() < m_equipLimit)
	{
		//��������𒴂��Ă��Ȃ���Α������X�g�ɒǉ�
		m_equipList.push_back(weaponStatus);
	}
}