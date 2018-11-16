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
	//座標とサイズを初期化
	m_basePos = { -560.0f, 180.0f };
	m_size = { 100.0f, 100.0f };
	//インベントリの背景を初期化
	m_backGroundTexture.Load(L"Assets/sprite/MenuUI/Back_Menu.png");
	m_backGround.Init(&m_backGroundTexture);
	//カーソルを初期化
	m_pointerTexture.Load(L"Assets/sprite/Pointer.png");
	m_pointer.Init(&m_pointerTexture);
	m_pointer.SetPosition(m_basePos);
	m_pointer.SetSize(m_size);
	//装備リストを取得
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//リストにアイテムがある
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//アイテムの種類を取得
			CWeaponManager::EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == CWeaponManager::enSword)
			{
				//剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeaponManager::enLongSword)
			{
				//大剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeaponManager::enArrow)
			{
				//弓
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].Init(itemTexure);
			}
			else if (weaponNum == CWeaponManager::enTwinSword)
			{
				//双剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].Init(itemTexure);
			}
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_size.x * (idx % m_width);
			position.y -= m_size.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//インベントリの幅を超えたら行を下げる
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_size);
			idx++;
		}
	}

	//ステータス表示を初期化
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	CVector2 fontPos = { m_basePos.x + m_size.x * m_width, m_basePos.y + m_size.y };
	wchar_t font[256];
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < enStatus_Num; i++)
		{
			switch (i)
			{
			case enStatus_Hp:
				swprintf(font, L"最大HP : %d", playerStatus.MaxHealth);
				break;
			case enStatus_Attack:
				swprintf(font, L"攻撃力 : %d", playerStatus.Strength);
				break;
			case enStatus_Defense:
				swprintf(font, L"防御力 : %d", playerStatus.Defense);
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
	//カーソル移動
	PointerMove();

	//装備する
	Equip();

	//ステータス計算
	CalucStatus();

	if (Pad().IsTriggerButton(enButtonB)) {
		//メニューに戻る
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
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < enStatus_Num; i++) {
			m_statusFont[j][i].Draw();
		}
	}
}

void CEquipInventory::PointerMove()
{
	CVector2 position = m_pointer.GetPosition();
	int number = m_pointerNum;
	float offset = m_size.x / 2.0f;
	if (Pad().IsTriggerButton(enButtonRight))
	{
		//右にカーソルを動かす
		position.x += m_size.x;
		number++;
		if (position.x > m_basePos.x + m_size.x * (m_width - 1) + offset)
		{
			//右端だった場合はそのまま
			position.x = m_basePos.x + m_size.x * (m_width - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonLeft))
	{
		//左にカーソルを動かす
		position.x -= m_size.x;
		number--;
		if (position.x < m_basePos.x - offset)
		{
			//左端だった場合はそのまま
			position.x = m_basePos.x;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonUp))
	{
		//上にカーソルを動かす
		position.y += m_size.y;
		number -= m_width;
		if (position.y > m_basePos.y + offset)
		{
			//上端だった場合はそのまま
			position.y = m_basePos.y;
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	else if (Pad().IsTriggerButton(enButtonDown))
	{
		//下にカーソルを動かす
		position.y -= m_size.y;
		number += m_width;
		if (position.y < m_basePos.y - m_size.y * (m_height - 1) - offset)
		{
			//下端だった場合はそのまま
			position.y = m_basePos.y - m_size.y * (m_height - 1);
		}
		else
		{
			//動いたらカーソルで選んでいる番号を更新
			m_pointerNum = number;
		}
	}
	//座標を更新
	m_pointer.SetPosition(position);
}

void CEquipInventory::Equip()
{
	//装備の数を取得
	size_t equipNum = m_equipList.size();
	if (m_pointerNum >= equipNum && !Pad().IsTriggerButton(enButtonA)) {
		return;
	}
	//カーソルで選んでいる装備をつける
	GetPlayer().GetWeaponManager().ChangeEquip(m_pointerNum);
	m_equipList = GetPlayer().GetWeaponManager().GetEquipList();
	m_width = 5;
	m_height = 1;
	if (!m_equipList.empty()) {
		//リストにアイテムがある
		int idx = 0;
		for (auto& equip : m_equipList)
		{
			//アイテムの種類を取得
			CWeaponManager::EnPlayerWeapon weaponNum = equip.weaponNum;
			if (weaponNum == CWeaponManager::enSword)
			{
				//剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/sword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == CWeaponManager::enLongSword)
			{
				//大剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/largeSword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == CWeaponManager::enArrow)
			{
				//弓
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/bow.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			else if (weaponNum == CWeaponManager::enTwinSword)
			{
				//双剣
				CTexture* itemTexure = TextureResource().LoadTexture(L"Assets/sprite/twinSword.png");
				m_equip[idx].SetTexture(itemTexure);
			}
			//座標とサイズを決める
			CVector2 position = m_basePos;
			position.x += m_size.x * (idx % m_width);
			position.y -= m_size.y * (idx / m_width);
			if (idx != 0 && idx % m_width == 0)
			{
				//インベントリの幅を超えたら行を下げる
				m_height++;
			}
			m_equip[idx].SetPosition(position);
			m_equip[idx].SetSize(m_size);
			idx++;
		}
	}
}

void CEquipInventory::CalucStatus()
{
	//装備の数を取得
	size_t equipNum = m_equipList.size();
	if (m_equipList.empty() && m_pointerNum >= equipNum) {
		return;
	}

	//装備変更した場合のステータスを計算する
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	std::list<CWeaponManager::SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < m_pointerNum; i++)
	{
		it++;
	}
	wchar_t font[256];
	for (int i = 0; i < enStatus_Num; i++)
	{
		int statusNum = 0;
		switch (i)
		{
		case enStatus_Hp:
			statusNum = playerStatus.MaxHealth;
			swprintf(font, L"最大HP : %d", statusNum);
			break;
		case enStatus_Attack:
			statusNum = (*it).attack + playerStatus.Strength;
			swprintf(font, L"攻撃力 : %d", statusNum);
			break;
		case enStatus_Defense:
			statusNum = (*it).diffence + playerStatus.Defense;
			swprintf(font, L"防御力 : %d", statusNum);
			break;
		}
		m_statusFont[1][i].SetString(font);
	}
}
